#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>
#include "xlsxwriter.h"

#include "funciones.h"
#include "DocenteCurso.h"
#include "DisponibilidadHoraria.h"
#include "HorarioSala.h"
#include <mpi.h>

using namespace std;


int main(int argc, char *argv[]){


    int proceso = 0;
    int procesos = 0;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    MPI_Comm_size(MPI_COMM_WORLD, &procesos);

    if(argc>5){
    // // ==============   Capturamos el nombre de los archivos Excel
    const char* nombreArchivoSalas = obtener_entrada(argv,argc,"-s");                      
    const char* nombreArchivoDocentes = obtener_entrada(argv,argc,"-d"); 
    const char* nombreArchivoCursos = obtener_entrada(argv,argc,"-c");

    //Vectores originales sin dividir    
    vector<DocenteCurso> vectorDocenteCurso = llenarVectorDocenteCurso(nombreArchivoCursos);
    vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHoraria(nombreArchivoDocentes);
    vector<HorarioSala> vectorHorarioSala = llenarVectorHorarioSala(nombreArchivoSalas);

    //Vectores divididos para trabajar en cada proceso
    vector<DocenteCurso> vectorDocenteCursoINF;
    vector<DocenteCurso> vectorDocenteCurso1;
    vector<DocenteCurso> vectorDocenteCurso2;
    vector<DocenteCurso> vectorDocenteCurso3;

    vector<HorarioSala> vectorHorarioLabs;
    vector<HorarioSala> vectorHorarioSala1;
    vector<HorarioSala> vectorHorarioSala2;
    vector<HorarioSala> vectorHorarioSala3;
    


    int contadorDocentes = 0;
    for(int docente = 0; docente < vectorDocenteCurso.size(); docente++){
        if(vectorDocenteCurso[docente].esINF()){
            vectorDocenteCursoINF.push_back(vectorDocenteCurso[docente]);
        }
        
        else{
            if(contadorDocentes < 55){
                vectorDocenteCurso1.push_back(vectorDocenteCurso[docente]);
                contadorDocentes++;
            }

            else if(contadorDocentes < 111){
                vectorDocenteCurso2.push_back(vectorDocenteCurso[docente]);
                contadorDocentes++;
            }

            else if(contadorDocentes < 167){
                vectorDocenteCurso3.push_back(vectorDocenteCurso[docente]);
                contadorDocentes++;
            }
        }
    }

    
    int contadorSalas = 0;
    for(int sala = 0; sala < vectorHorarioSala.size(); sala++){
        if(vectorHorarioSala[sala].esUnLab()){
            vectorHorarioLabs.push_back(vectorHorarioSala[sala]);
        }
        
        else{
            if(contadorSalas < 11){
                vectorHorarioSala1.push_back(vectorHorarioSala[sala]);
                contadorSalas++;
            }

            else if(contadorSalas < 23){
                vectorHorarioSala2.push_back(vectorHorarioSala[sala]);
                contadorSalas++;
            }

            else if(contadorSalas < 35){
                vectorHorarioSala3.push_back(vectorHorarioSala[sala]);
                contadorSalas++;
            }
        }
    }


    if(proceso == 0){
        for(int docente = 0; docente < vectorDocenteCurso1.size(); docente++){
            int salaFinal;
            int bloqueFinal;
            int diaFinal;

            string identificadorDocente = vectorDocenteCurso1[docente].retornaIdentificador();
            vector<vector<bool>> matrizDisponibilidadDocente = retornaMatrizPorDocente(vectorDisponibilidad, vectorDocenteCurso1[docente].retornaIdDocente());

            while(vectorDocenteCurso1[docente].retornaBloquesDisponibles() > 0){
                int bloquesDisponiblesOriginal = vectorDocenteCurso1[docente].retornaBloquesDisponibles();
                
                int primeraSala = 0;
                int ultimaSala = 10;
                
                //Se recorren todos los labs por cada DocenteCurso   
                for(int sala = primeraSala; sala <= ultimaSala; sala++){
                    
                    //Se recorren los días de la semana
                    for(int dia = 0; dia < 6; dia++){
                        //Si es un día de lunes a viernes
                        if(dia != 5){
                            for(int bloque = 0; bloque < 7; bloque++){
                                if(vectorHorarioSala1[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && !hayCuatroBloquesSeguidos(identificadorDocente, bloque, dia, vectorHorarioSala1[sala].retornaMatrizHorario()) && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioSala1[sala].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCurso1[docente].restaBloquesDisponibles();

                                    break;                                                       
                                }                                   
                            }
                        }
                        //Si es sábado
                        else{
                            for(int bloque = 0; bloque < 4; bloque++){
                                if(vectorHorarioSala1[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioSala1[sala].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCurso1[docente].restaBloquesDisponibles();

                                    break;
                                                                                
                                }
                                bloqueFinal = bloque;                                                                      
                            }

                        }
                        if(bloquesDisponiblesOriginal > vectorDocenteCurso1[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                    
                        diaFinal = dia;
                    }
                    if(bloquesDisponiblesOriginal > vectorDocenteCurso1[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer

                    salaFinal = sala;
                }
                

                //Se realiza la salida del bucle en el caso de que no sea posible seguir llenando el horario con este DocenteCurso
                
                if(bloqueFinal == 3 && diaFinal == 5 && salaFinal == 10){
                    break;
                }        
            }//Mientras los bloques disponibles sean mayor a 0    
        }
        
    }

  if(proceso == 1){
        for(int docente = 0; docente < vectorDocenteCurso2.size(); docente++){
            int salaFinal;
            int bloqueFinal;
            int diaFinal;

            string identificadorDocente = vectorDocenteCurso2[docente].retornaIdentificador();
            vector<vector<bool>> matrizDisponibilidadDocente = retornaMatrizPorDocente(vectorDisponibilidad, vectorDocenteCurso2[docente].retornaIdDocente());

            while(vectorDocenteCurso2[docente].retornaBloquesDisponibles() > 0){
                int bloquesDisponiblesOriginal = vectorDocenteCurso2[docente].retornaBloquesDisponibles();
                
                int primeraSala = 0;
                int ultimaSala = 11;
                
                //Se recorren todos los labs por cada DocenteCurso   
                for(int sala = primeraSala; sala <= ultimaSala; sala++){
                    
                    //Se recorren los días de la semana
                    for(int dia = 0; dia < 6; dia++){
                        //Si es un día de lunes a viernes
                        if(dia != 5){
                            for(int bloque = 0; bloque < 7; bloque++){
                                if(vectorHorarioSala2[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && !hayCuatroBloquesSeguidos(identificadorDocente, bloque, dia, vectorHorarioSala2[sala].retornaMatrizHorario()) && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioSala2[sala].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCurso2[docente].restaBloquesDisponibles();

                                    break;                                                       
                                }                                   
                            }
                        }
                        //Si es sábado
                        else{
                            for(int bloque = 0; bloque < 4; bloque++){
                                if(vectorHorarioSala2[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioSala2[sala].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCurso2[docente].restaBloquesDisponibles();

                                    break;
                                                                                
                                }
                                bloqueFinal = bloque;                                                                      
                            }

                        }
                        if(bloquesDisponiblesOriginal > vectorDocenteCurso2[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                    
                        diaFinal = dia;
                    }
                    if(bloquesDisponiblesOriginal > vectorDocenteCurso2[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer

                    salaFinal = sala;
                }
                

                //Se realiza la salida del bucle en el caso de que no sea posible seguir llenando el horario con este DocenteCurso
                
                if(bloqueFinal == 3 && diaFinal == 5 && salaFinal == 11){
                    break;
                }        
            }//Mientras los bloques disponibles sean mayor a 0    
        }
    }

    if(proceso == 2){
        for(int docente = 0; docente < vectorDocenteCurso3.size(); docente++){
            int salaFinal;
            int bloqueFinal;
            int diaFinal;

            string identificadorDocente = vectorDocenteCurso3[docente].retornaIdentificador();
            vector<vector<bool>> matrizDisponibilidadDocente = retornaMatrizPorDocente(vectorDisponibilidad, vectorDocenteCurso3[docente].retornaIdDocente());

            while(vectorDocenteCurso3[docente].retornaBloquesDisponibles() > 0){
                int bloquesDisponiblesOriginal = vectorDocenteCurso3[docente].retornaBloquesDisponibles();
                
                int primeraSala = 0;
                int ultimaSala = 11;
                
                //Se recorren todos los labs por cada DocenteCurso   
                for(int sala = primeraSala; sala <= ultimaSala; sala++){
                    
                    //Se recorren los días de la semana
                    for(int dia = 0; dia < 6; dia++){
                        //Si es un día de lunes a viernes
                        if(dia != 5){
                            for(int bloque = 0; bloque < 7; bloque++){
                                if(vectorHorarioSala3[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && !hayCuatroBloquesSeguidos(identificadorDocente, bloque, dia, vectorHorarioSala3[sala].retornaMatrizHorario()) && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioSala3[sala].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCurso3[docente].restaBloquesDisponibles();

                                    break;                                                       
                                }                                   
                            }
                        }
                        //Si es sábado
                        else{
                            for(int bloque = 0; bloque < 4; bloque++){
                                if(vectorHorarioSala3[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioSala3[sala].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCurso3[docente].restaBloquesDisponibles();

                                    break;
                                                                                
                                }
                                bloqueFinal = bloque;                                                                      
                            }

                        }
                        if(bloquesDisponiblesOriginal > vectorDocenteCurso3[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                    
                        diaFinal = dia;
                    }
                    if(bloquesDisponiblesOriginal > vectorDocenteCurso3[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer

                    salaFinal = sala;
                }
                

                //Se realiza la salida del bucle en el caso de que no sea posible seguir llenando el horario con este DocenteCurso
                
                if(bloqueFinal == 3 && diaFinal == 5 && salaFinal == 11){
                    break;
                }        
            }//Mientras los bloques disponibles sean mayor a 0    
        }
    }

    if(proceso == 3){
        for(int docente = 0; docente < vectorDocenteCursoINF.size(); docente++){
            int salaFinal;
            int bloqueFinal;
            int diaFinal;

            string identificadorDocente = vectorDocenteCursoINF[docente].retornaIdentificador();
            vector<vector<bool>> matrizDisponibilidadDocente = retornaMatrizPorDocente(vectorDisponibilidad, vectorDocenteCursoINF[docente].retornaIdDocente());

            while(vectorDocenteCursoINF[docente].retornaBloquesDisponibles() > 0){
                int bloquesDisponiblesOriginal = vectorDocenteCursoINF[docente].retornaBloquesDisponibles();
                
                int primeraSala = 0;
                int ultimaSala = 5;
                
                //Se recorren todos los labs por cada DocenteCurso   
                for(int sala = primeraSala; sala <= ultimaSala; sala++){
                    
                    //Se recorren los días de la semana
                    for(int dia = 0; dia < 6; dia++){
                        //Si es un día de lunes a viernes
                        if(dia != 5){
                            for(int bloque = 0; bloque < 7; bloque++){
                                if(vectorHorarioLabs[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && !hayCuatroBloquesSeguidos(identificadorDocente, bloque, dia, vectorHorarioLabs[sala].retornaMatrizHorario()) && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioLabs[sala].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCursoINF[docente].restaBloquesDisponibles();

                                    break;                                                       
                                }                                   
                            }
                        }
                        //Si es sábado
                        else{
                            for(int bloque = 0; bloque < 4; bloque++){
                                if(vectorHorarioLabs[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioLabs[sala].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCursoINF[docente].restaBloquesDisponibles();

                                    break;
                                                                                
                                }
                                bloqueFinal = bloque;                                                                      
                            }

                        }
                        if(bloquesDisponiblesOriginal > vectorDocenteCursoINF[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                    
                        diaFinal = dia;
                    }
                    if(bloquesDisponiblesOriginal > vectorDocenteCursoINF[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer

                    salaFinal = sala;
                }
                

                //Se realiza la salida del bucle en el caso de que no sea posible seguir llenando el horario con este DocenteCurso
                
                if(bloqueFinal == 3 && diaFinal == 5 && salaFinal == 5){
                    break;
                }        
            }//Mientras los bloques disponibles sean mayor a 0    
        }
    }

     if(proceso == 0){
         string archivo = "archivo1.xlsx";
        escribirExcel(vectorHorarioSala1, archivo);
    }

    if(proceso == 1){
        string archivo = "archivo2.xlsx";
        escribirExcel(vectorHorarioSala2, archivo);
    }

    if(proceso == 2){
        string archivo = "archivo3.xlsx";
        escribirExcel(vectorHorarioSala3, archivo);
    }

    if(proceso == 3){
        string archivo = "archivoLabs.xlsx";
        escribirExcel(vectorHorarioLabs, archivo);
    }
    
    

    

    } else{
        cout << "Argumentos insuficientes o incorrectos" <<endl;
        cout<< " -d Docentes.xlsx -c Cursos.xlsx -s Salas.xlsx" <<endl;
        return EXIT_FAILURE;
    }

    
    MPI_Finalize();
    
    return 0;
}

