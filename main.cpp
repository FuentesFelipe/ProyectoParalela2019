#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>
#include "xlsxwriter.h"
#include <ctime>
#include "funciones.h"
#include "DocenteCurso.h"
#include "DisponibilidadHoraria.h"
#include "HorarioSala.h"
#include <mpi.h>

using namespace std;

int main(int argc, char *argv[]){

    unsigned t0, t1;

    t0 = clock();
    
    if(argc>5){
        
        // ======   Capturamos el nombre de los archivos Excel

        const char* nombreArchivoSalas = obtener_entrada(argv,argc,"-s");                      
        const char* nombreArchivoDocentes = obtener_entrada(argv,argc,"-d"); 
        const char* nombreArchivoCursos = obtener_entrada(argv,argc,"-c");

        // ======   Inicializamos los vectores GLOBALES con toda la información del Excel    

        vector<DocenteCurso> vectorDocenteCurso = llenarVectorDocenteCurso(nombreArchivoCursos);
        vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHoraria(nombreArchivoDocentes);
        vector<HorarioSala> vectorHorarioSala = llenarVectorHorarioSala(nombreArchivoSalas);
            
        // ======   Definicion variables Globales

        int procesadorID;         
        int totalProcesadores;
        int rango[4]; //Arreglo que almacenará un indice de INICIO y otro de FIN Para Docentes y Salas

        vector<DocenteCurso> vectorCursosNOINF; // Para repartir entre procesadores
        vector<HorarioSala> vectorSalasNOLAB;   // Para repartir entre procesadores
        vector<DocenteCurso> vectorCursosINF;   // Para el procesasdor Coordinador 0

        // ====== Creamos vector para Cursos INF. El resto de cursos, en otro vector

        bool yaSeAgrego;
        int contadorCursos; 

        for( int curso = 0; curso < vectorDocenteCurso.size() ; curso++){
            yaSeAgrego = false;
            contadorCursos=0;

            if(vectorDocenteCurso[curso].esINF()){
                vectorCursosINF.push_back(vectorDocenteCurso[curso]);
            }
                
            else{
                vectorCursosNOINF.push_back(vectorDocenteCurso[curso]);
            }                    
        }

        int primerLAB;
        int ultimoLAB;
        bool primero;

        // ===== Capturamos el intervalo donde se encuentran las Salas LAB en el vector de Salas
            //   Creamos un vector de Salas distintas a LABORATORIOS
        
        for( int LAB = 0; LAB < vectorHorarioSala.size() ; LAB++){
            
            if(vectorHorarioSala[LAB].esLAB()){
                
                if(!primero){

                    primerLAB = LAB;
                    primero = true;
                
                }
                ultimoLAB= LAB;
            }                
            else{
                vectorSalasNOLAB.push_back(vectorHorarioSala[LAB]);
            }                
        }
        
       
        // ==== Inicio OpenMPI
        
        MPI_Init(&argc, &argv);                                         /*START MPI */
        MPI_Comm_rank(MPI_COMM_WORLD, &procesadorID);                   /*DETERMINE RANK OF THIS PROCESSOR*/
        MPI_Comm_size(MPI_COMM_WORLD, &totalProcesadores);              /*DETERMINE TOTAL NUMBER OF PROCESSORS*/
        MPI_Status stat;
        
        // ==== EL PROCESADOR 0 SERÁ EL COORDINADOR. Asignara horarios a cursos INF en LABS
        if(procesadorID==0){

        // ==== Repartición de Docentes y Salas entre los n-1 procesadores restantes    

            int fuente;

            // === Cantidad de Cursos y Salas para cada Procesador
            int segmentoDeCursos = (vectorCursosNOINF.size()/(totalProcesadores - 1));
            int segmentoSalasNOLAB = vectorSalasNOLAB.size()/(totalProcesadores -1);  
            
            for(fuente = 1; fuente <totalProcesadores; fuente++){
                
                rango[0] = (fuente - 1)*segmentoDeCursos;
                rango[1] = segmentoDeCursos*fuente;
                rango[2] = (fuente - 1)*segmentoSalasNOLAB;
                rango[3] = segmentoSalasNOLAB*fuente;

                if(fuente + 1 == totalProcesadores){ 

                    // Se agregan los cursos y salas restantes al último procesador
                    rango[1] += vectorCursosNOINF.size() - rango[1];
                    rango[3] += vectorSalasNOLAB.size() - rango[3];
                }
                
                // Enviamos los intervalos que contienen a los cursos y salas a cada Procesador
                MPI_Send(&rango,sizeof(rango),MPI_INT,fuente,1,MPI_COMM_WORLD);
            }

            //=== Asignación de horario a Cursos INF en LABSint labFinal;
                int salaFinal;
                int bloqueFinal;
                int diaFinal;
                int labFinal;
                int IDdocente;
                
                string codigoCurso;                
                for(int curso = 0; curso < vectorCursosINF.size(); curso++){             

                codigoCurso =vectorCursosINF[curso].retornaIdentificador();
                IDdocente = vectorCursosINF[curso].retornaIdDocente();

                vector<vector<bool>> matrizDisponibilidadDocente = retornaMatrizPorDocente(vectorDisponibilidad,IDdocente);

                //Mientras existan bloques pedagógicos por ASIGNAR para un curso INF
                while(vectorCursosINF[curso].retornaBloquesDisponibles() > 0){
                    
                    int bloquesDisponiblesOriginal =vectorCursosINF[curso].retornaBloquesDisponibles();
                                        
                    //Se recorren solo los labs por cada CURSO INF   
                    for(int lab = primerLAB; lab < ultimoLAB ; lab++){
                        
                        //Se recorren los días de la semana
                        for(int dia = 0; dia < DIAS; dia++){
                    
                            //Si es un día de lunes a viernes
                            if(dia != 5){
                                for(int bloque = 0; bloque < BLOQUES; bloque++){
                                    if(vectorHorarioSala[lab].retornaMatrizHorario()[bloque][dia] == "Disponible" && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                        
                                        vectorHorarioSala[lab].llenarBloque(codigoCurso, bloque, dia); //Asignamos bloque en el LAB

                                        vectorCursosINF[curso].restaBloquesDisponibles();               
                                        break;                                                  
                                    }                                   
                                }
                            }
                            //Si es sábado
                            else{
                                for(int bloque = 0; bloque < 4; bloque++){
                                    if(vectorHorarioSala[lab].retornaMatrizHorario()[bloque][dia] == "Disponible" && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                        
                                        vectorHorarioSala[lab].llenarBloque(codigoCurso, bloque, dia);

                                        vectorCursosINF[curso].restaBloquesDisponibles();
                                        break;
                                                                                    
                                    }
                                    bloqueFinal = bloque;                                                                      
                                }

                            }
                            if(bloquesDisponiblesOriginal >vectorCursosINF[curso].retornaBloquesDisponibles()){
                                break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer

                            }
                                                        
                            diaFinal = dia;
                        }
                        if(bloquesDisponiblesOriginal >vectorCursosINF[curso].retornaBloquesDisponibles()){
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                        }
                                

                        labFinal = lab;
                    }                                   
                        
                }//Mientras los bloques disponibles sean mayor a 0    
            }

                                    
        } else{
            /*
            *       ASIGNACIÓN DE CURSOS NO INF EN SALAS - DE FORMA PARALELA
            * 
            *       Realiza la misma lógica de asignación en Procesador 0
            *       con la diferencia de que no ingresa un bloque a la Sala,
            *       sino, guarda el ID de Sala, del Curso, el día y el bloque (enteros)
            *       en un vector.
            * 
            *       El vector resultante es enviado al procesador cero.
            * 
            *  */

            vector<int> vectorParaEnvio;
            MPI_Recv(&rango,sizeof(rango),MPI_INT,0,1,MPI_COMM_WORLD,&stat);
                        
            int labFinal;
            int salaFinal;
            int bloqueFinal;
            int diaFinal;

            int bloquesDisponiblesOriginal;
            int primeraSala;
            int ultimaSala;
            int salaEnVectorOriginal;
            int ramoEnVectorOriginal;
            bool encontrado;
            string codigoCurso;

            for(int curso = rango[0]; curso < rango[1]; curso++){
            
                codigoCurso = vectorCursosNOINF[curso].retornaIdentificador();
                vector<vector<bool>> matrizDisponibilidadDocente = retornaMatrizPorDocente(vectorDisponibilidad, vectorCursosNOINF[curso].retornaIdDocente());

                while(vectorCursosNOINF[curso].retornaBloquesDisponibles() > 0){

                    bloquesDisponiblesOriginal = vectorCursosNOINF[curso].retornaBloquesDisponibles();                                   
                    primeraSala = rango[2];
                    ultimaSala = rango[3];
                                            
                    //Se recorren todas las salas por cada DocenteCurso de INF    
                    for(int sala = primeraSala; sala < ultimaSala; sala++){
                        //Se recorren los días de la semana
                        for(int dia = 0; dia < DIAS; dia++){
                            //Si es un día de lunes a viernes
                            if(dia != 5){
                                for(int bloque = 0; bloque < BLOQUES; bloque++){
                                    if(vectorSalasNOLAB[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                        
                                        vectorSalasNOLAB[sala].llenarBloque(codigoCurso, bloque, dia);
                                        vectorCursosNOINF[curso].restaBloquesDisponibles();
                                        
                                        salaEnVectorOriginal=0;
                                        encontrado = false;
                                        
                                        //Buscamos el índice de posición del Curso y Ramo en los Vectores GLOBALES
                                        while(salaEnVectorOriginal< vectorHorarioSala.size() && !encontrado){
                                            if(vectorHorarioSala[salaEnVectorOriginal].retornaNombreSala() == vectorSalasNOLAB[sala].retornaNombreSala()){

                                                vectorParaEnvio.push_back(salaEnVectorOriginal);
                                                encontrado=true;

                                            }                                
                                            salaEnVectorOriginal++;
                                        }

                                        vectorParaEnvio.push_back(bloque);
                                        vectorParaEnvio.push_back(dia);
                                        
                                        encontrado = false;
                                        ramoEnVectorOriginal=0;
                                        while(ramoEnVectorOriginal< vectorDocenteCurso.size() && !encontrado){
                                            if(vectorDocenteCurso[ramoEnVectorOriginal].retornaIdentificador()==vectorCursosNOINF[curso].retornaIdentificador()){
                                                
                                                vectorParaEnvio.push_back(ramoEnVectorOriginal);
                                                encontrado = true;
                                            }                      
                                            ramoEnVectorOriginal++;                         
                                        }

                                        break;                                                       
                                    }                                   
                                }
                            }
                            //Si es sábado
                            else{
                                for(int bloque = 0; bloque < 4; bloque++){
                                    if(vectorSalasNOLAB[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                        
                                        vectorSalasNOLAB[sala].llenarBloque(codigoCurso, bloque, dia);
                                        vectorCursosNOINF[curso].restaBloquesDisponibles();

                                        salaEnVectorOriginal=0;
                                        encontrado = false;
                                        while(salaEnVectorOriginal< vectorHorarioSala.size() && !encontrado){
                                            if(vectorHorarioSala[salaEnVectorOriginal].retornaNombreSala() == vectorSalasNOLAB[sala].retornaNombreSala()){
                                                vectorParaEnvio.push_back(salaEnVectorOriginal);
                                                encontrado=true;
                                            }                      
                                            salaEnVectorOriginal++;          
                                        }

                                        vectorParaEnvio.push_back(bloque);
                                        vectorParaEnvio.push_back(dia);

                                        encontrado = false;
                                        ramoEnVectorOriginal=0;
                                        while(ramoEnVectorOriginal< vectorDocenteCurso.size() && !encontrado){
                                            if(vectorDocenteCurso[ramoEnVectorOriginal].retornaIdentificador()==vectorCursosNOINF[curso].retornaIdentificador()){
                                                vectorParaEnvio.push_back(ramoEnVectorOriginal);
                                                encontrado = true;
                                            }                      
                                            ramoEnVectorOriginal++;                         
                                        }
                                        break;
                                                                                    
                                    }
                                    bloqueFinal = bloque;                                                                      
                                }

                            }
                            if(bloquesDisponiblesOriginal > vectorCursosNOINF[curso].retornaBloquesDisponibles()){
                                break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                            }
                                
                        
                            diaFinal = dia;
                        }
                        if(bloquesDisponiblesOriginal > vectorCursosNOINF[curso].retornaBloquesDisponibles()){
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                        }
                                

                        salaFinal = sala;
                    }
                    
     
                }//While (bloquesPorAsignar)
            }      
  
            int largo= vectorParaEnvio.size()+1; //
            
            //=== Arreglo con índices,dias y bloques para ser enviado a PRO 0 
            int arregloParaEnviar[largo];
            arregloParaEnviar[0] = largo; //Almacenamos el largo del arreglo en el primer elemento

            for(int elemento = 0; elemento< largo; elemento++){

                // Se copia el vector Con Indices al arreglo Para Enviar
                arregloParaEnviar[elemento+1] = vectorParaEnvio[elemento];                                
            }

            MPI_Send(&arregloParaEnviar,largo, MPI_INT,0,1,MPI_COMM_WORLD);
        }

        if(procesadorID == 0){

            //Recepción de índices de cada asignación realizada por cada Procesador
            

            for(int procesadores= 1; procesadores < totalProcesadores;procesadores++){
                
                int arregloBuffer[3000];
                MPI_Recv(&arregloBuffer,3000, MPI_INT,procesadores,1,MPI_COMM_WORLD,&stat);
                
                int dia, bloque;
                string identificadorCursoDocente;
                // el arreglo contiene (IndiceSala, bloque, dia, Indice Curso-Docente)
                for(int elemento = 1; elemento+4 <= arregloBuffer[0]; elemento=elemento+4){
                    
                    identificadorCursoDocente = vectorDocenteCurso[arregloBuffer[elemento+3]].retornaIdentificador();
                    bloque = arregloBuffer[elemento + 1];
                    dia = arregloBuffer[elemento + 2];
                    
                    // Ahora se realiza la asignación de salas al Vector GLOBAL
                    vectorHorarioSala[arregloBuffer[elemento]].llenarBloque(identificadorCursoDocente,bloque,dia);
                }
                
            }

            escribirExcel(vectorHorarioSala,"HorarioCursoProfesores.xlsx");
            cout<<endl<<"Se ha creado el archivo HorarioCursoProfesores.xlsx"<<endl;
            
            t1 = clock();

            double time = (double(t1-t0)/CLOCKS_PER_SEC);
            
            cout << "Execution Time: " << time << " segundos. "<< endl<<endl;
                    
        }
        MPI_Finalize();   
       
    } else{
        cout << "Argumentos insuficientes o incorrectos" <<endl;
        cout<< " -d Docentes.xlsx -c Cursos.xlsx -s Salas.xlsx" <<endl;
        return EXIT_FAILURE;
    }
    
    return 0;
}