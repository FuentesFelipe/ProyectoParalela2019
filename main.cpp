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

    if(argc>5){
    // ==============   Capturamos el nombre de los archivos Excel
    const char* nombreArchivoSalas = obtener_entrada(argv,argc,"-s");                      
    const char* nombreArchivoDocentes = obtener_entrada(argv,argc,"-d"); 
    const char* nombreArchivoCursos = obtener_entrada(argv,argc,"-c");
        
    vector<DocenteCurso> vectorDocenteCurso = llenarVectorDocenteCurso(nombreArchivoCursos);
    vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHoraria(nombreArchivoDocentes);
    vector<HorarioSala> vectorHorarioSala = llenarVectorHorarioSala(nombreArchivoSalas);

    
    //Se recorre una vez por cada objeto DocenteCurso
    for(int docente = 0; docente < vectorDocenteCurso.size(); docente++){
        int labFinal;
        int salaFinal;
        int bloqueFinal;
        int diaFinal;

        string identificadorDocente = vectorDocenteCurso[docente].retornaIdentificador();
        vector<vector<bool>> matrizDisponibilidadDocente = retornaMatrizPorDocente(vectorDisponibilidad, vectorDocenteCurso[docente].retornaIdDocente());

        while(vectorDocenteCurso[docente].retornaBloquesDisponibles() > 0){
            // cout << "Soy el docente: " << docente+2 << endl;
            int bloquesDisponiblesOriginal = vectorDocenteCurso[docente].retornaBloquesDisponibles();
            
            
            if(vectorDocenteCurso[docente].esINF()){
                int primerLab = 35;
                int ultimoLab = 40;
                
                //Se recorren todos los labs por cada DocenteCurso de INF    
                for(int lab = primerLab; lab <= ultimoLab; lab++){
                    
                    //Se recorren los días de la semana
                    for(int dia = 0; dia < 6; dia++){
                        //Si es un día de lunes a viernes
                        if(dia != 5){
                            for(int bloque = 0; bloque < 7; bloque++){
                                if(vectorHorarioSala[lab].retornaMatrizHorario()[bloque][dia] == "Disponible" && !hayCuatroBloquesSeguidos(identificadorDocente, bloque, dia, vectorHorarioSala[lab].retornaMatrizHorario()) && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    
                                    vectorHorarioSala[lab].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCurso[docente].restaBloquesDisponibles();

                                    break;                                                  
                                }                                   
                            }
                        }
                        //Si es sábado
                        else{
                            for(int bloque = 0; bloque < 4; bloque++){
                                if(vectorHorarioSala[lab].retornaMatrizHorario()[bloque][dia] == "Disponible" && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioSala[lab].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCurso[docente].restaBloquesDisponibles();

                                    break;
                                                                                
                                }
                                bloqueFinal = bloque;                                                                      
                            }

                        }
                        if(bloquesDisponiblesOriginal > vectorDocenteCurso[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                    
                        diaFinal = dia;
                    }
                    if(bloquesDisponiblesOriginal > vectorDocenteCurso[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer

                    labFinal = lab;
                }
            }                

            //Se verifica que el DocenteCurso no sea de INF
            else{
                int primeraSala = 0;
                int ultimaSala = 34;
                
                //Se recorren todos los labs por cada DocenteCurso de INF    
                for(int sala = primeraSala; sala <= ultimaSala; sala++){
                    
                    //Se recorren los días de la semana
                    for(int dia = 0; dia < 6; dia++){
                        //Si es un día de lunes a viernes
                        if(dia != 5){
                            for(int bloque = 0; bloque < 7; bloque++){
                                if(vectorHorarioSala[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && !hayCuatroBloquesSeguidos(identificadorDocente, bloque, dia, vectorHorarioSala[sala].retornaMatrizHorario()) && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioSala[sala].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCurso[docente].restaBloquesDisponibles();

                                    break;                                                       
                                }                                   
                            }
                        }
                        //Si es sábado
                        else{
                            for(int bloque = 0; bloque < 4; bloque++){
                                if(vectorHorarioSala[sala].retornaMatrizHorario()[bloque][dia] == "Disponible" && tieneDisponibilidad(bloque, dia, matrizDisponibilidadDocente)){
                                    vectorHorarioSala[sala].llenarBloque(identificadorDocente, bloque, dia);

                                    vectorDocenteCurso[docente].restaBloquesDisponibles();

                                    break;
                                                                                
                                }
                                bloqueFinal = bloque;                                                                      
                            }

                        }
                        if(bloquesDisponiblesOriginal > vectorDocenteCurso[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                    
                        diaFinal = dia;
                    }
                    if(bloquesDisponiblesOriginal > vectorDocenteCurso[docente].retornaBloquesDisponibles())
                            break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer

                    salaFinal = sala;
                }
            }

            //Se realiza la salida del bucle en el caso de que no sea posible seguir llenando el horario con este DocenteCurso
            if(vectorDocenteCurso[docente].esINF()){
                if(bloqueFinal == 3 && diaFinal == 5 && labFinal == 40){
                    break;
                }
            }

            else{
                if(bloqueFinal == 3 && diaFinal == 5 && salaFinal == 34){
                    break;
                }
            }

                
        }//Mientras los bloques disponibles sean mayor a 0    
    }

    escribirExcel(vectorHorarioSala);
    for(int i = 0; i < vectorHorarioSala.size(); i++){
        vectorHorarioSala[i].mostrarDatos();
    }
    
    } else{
        cout << "Argumentos insuficientes o incorrectos" <<endl;
        cout<< " -d Docentes.xlsx -c Cursos.xlsx -s Salas.xlsx" <<endl;
        return EXIT_FAILURE;
    }
    return 0;
}