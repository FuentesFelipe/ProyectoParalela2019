#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>
#include "funciones.h"
#include "docente_curso.h"
#include "disponibilidad_horaria.h"
#include <stdio.h>
#include <string.h>

using namespace std;

vector<string> vectorDias = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};

int main(int argc, char *argv[]){
    /*
    *   Main con llamadas a funciones para revisar el comportamiento de las funciones globales
    *   
    *   El nombre de los archivos entrarán como argumento del main
    * 
    *  */


    // =============     *PROVISORIO   Nombre de los archivos ==============
    const char* nombreArchivo = "Salas.xlsx";                      
    const char* nombreArchivoDocentes = "Docentes.xlsx";
    const char* nombreArchivoCursos = "Cursos.xlsx";
    
    // =============    Creación y lectura del Vector con DocenteCursos      ==============
    vector<DocenteCurso> vectorDocentes = llenarVectorDocenteCursoNew(nombreArchivoCursos);
    mostrarVectorDocenteCurso(vectorDocentes);
    
    // =============    Creación y lectura del vector con Salas ==============
    vector<string> vectorSalas = llenarArregloSalas(nombreArchivo);               
    mostrarArregloSalas(vectorSalas);                            
    
    // =============    Creación objetos Salas para ser Escritas en Excel ==============
    vector<MatrizSala> vectorConSalasVacias = crearVectorConSalasVacias(vectorSalas); 
    
    // =============    Creación y lectura del vector con objetos Disponibilidad Horaria ==============
    vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHorariaNew(nombreArchivoDocentes, vectorDias);
    for(int i = 0; i < vectorDisponibilidad.size(); i++)
         vectorDisponibilidad[i].mostrarDatos();

    // =============    Escritura en Excel con las Salas Vacias ==============
    
    escribirExcel(vectorConSalasVacias, vectorDias); // Genera el excel de Salida Horario.xlsx





    int bloquesRamo,i,j,k,l,m, count =0;
    char *contenido;
    

    // for(int h = 0; h < vectorConSalasVacias.size(); h++){
    //     MatrizSala *salaAnalizada = &vectorConSalasVacias[h];

    //     cout<<"salaAnalizada->getBloques() "<< salaAnalizada->getBloquesDisponibles()<<endl;

    //     while(salaAnalizada->getBloquesDisponibles()>0){
    //         for(i=0; i < vectorDisponibilidad.size(); i++){
    //             DisponibilidadHoraria *matrizDisponibilidad = &vectorDisponibilidad[i];
    //             int bloquesFreeDocente = matrizDisponibilidad->getCantidadBloquesLibres();
    //             cout<<"matriz->quedan por rellenar() "<< bloquesFreeDocente<<endl;
    //             while(bloquesFreeDocente>0){
    //                 for(j=0; j<vectorDocentes.size(); j++){
                
    //                 DocenteCurso *docente= &vectorDocentes[j];
    //                 if(docente->getIdProfe()==matrizDisponibilidad->getIdDocente()){ //OK
    //                     string codigo = docente->getCodigoCurso();
    //                     int profe = docente->getIdProfe();
    //                     cout<< "BloquesFreeDocentes "<<bloquesFreeDocente<<endl;
    //                     char * lala= "lala";
    //                     //char *buf = strcpy(buf,(codigo += char(profe)).c_str());
    //                     //cout<<"buf"<< buf<<endl;
    //                     //salaAnalizada->insertarBloque();
    //                     count++;
    //                     cout<< salaAnalizada->getIdSala() <<" "
    //                     << salaAnalizada->getBloquesDisponibles()<< " "
    //                     << matrizDisponibilidad->getIdDocente()<<" "
    //                     << docente->getIdProfe()<< " "
    //                     << docente->getCodigoCurso() << " bloquesTotales "
    //                     << docente->getBloquesTotalesRamo()<<" count "
    //                     <<count<<endl<<endl;
    //                     // while(bloquesFreeDocente>0){
    //                     //     for(k = 0; k<DIAS; k++){
    //                     //         for(l = 0; l<BLOQUES; l++){
                                    
    //                     //             if(salaAnalizada->consultarDispDia(l,k)){
    //                     //                 count++;
    //                     //                 //string codigo = docente->getCodigoCurso();
    //                     //                 //int profe = docente->getIdProfe();
    //                     //                 //char *buf = strcpy(buf,(codigo += "-" + profe).c_str());            
    //                     //                 //salaAnalizada->insertarBloque(l,k,VACIA);
    //                     //                 bloquesFreeDocente--;            
    //                     //                 //matrizDisponibilidad->setDisponibilidad(k,l);
    //                     //                 cout<< docente->getIdProfe()<<" "<< docente->getCodigoCurso()<< count<<endl;
    //                     //             }
    //                     //         }
    //                     //     }                        
    //                     // }

    //                     salaAnalizada->insertarBloque(1,1,lala);
                        
    //                 }
    //             }
    //             bloquesFreeDocente--;
    //             }

    //     }

    //     }

    // }
     
    return 0;
    
}