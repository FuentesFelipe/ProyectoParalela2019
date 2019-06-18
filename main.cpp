#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <xlsxio_read.h>
#include "funciones.h"
#include "docente_curso.h"
#include "disponibilidad_horaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

vector<string> vectorDias = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};

int main(int argc, char *argv[]){

    if(argc> 5){ // Cambiar cuando se implemente maquinas txt
            /*
        *   Main con llamadas a funciones para revisar el comportamiento de las funciones globales
        *   
        *   El nombre de los archivos entrarán como argumento del main
        * 
        *  */


        // =============     *PROVISORIO   Nombre de los archivos ==============

        
        const char* nombreArchivoSalas = obtener_entrada(argv,argc,"-s");                      
        const char* nombreArchivoDocentes = obtener_entrada(argv,argc,"-d"); 
        const char* nombreArchivoCursos = obtener_entrada(argv,argc,"-c");

        // =============    Creación y lectura del Vector con DocenteCursos      ==============
        vector<DocenteCurso> vectorDocentes = llenarVectorDocenteCursoNew(nombreArchivoCursos);
        mostrarVectorDocenteCurso(vectorDocentes);
        
        // =============    Creación y lectura del vector con Salas ==============
        vector<string> vectorSalas = llenarArregloSalas(nombreArchivoSalas);               
        mostrarArregloSalas(vectorSalas);                            
        
        // =============    Creación objetos Salas para ser Escritas en Excel ==============
        vector<MatrizSala> vectorConSalasVacias = crearVectorConSalasVacias(vectorSalas); 
        
        // =============    Creación y lectura del vector con objetos Disponibilidad Horaria ==============
        vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHorariaNew(nombreArchivoDocentes, vectorDias);
        for(int i = 0; i < vectorDisponibilidad.size(); i++)
            vectorDisponibilidad[i].mostrarDatos();

        // =============    Escritura en Excel con las Salas Vacias ==============
        

        //escribirExcel(vectorConSalasVacias, vectorDias); // Genera el excel de Salida Horario.xlsx


        //int bloquesRamo,i,j,k,l,m, count =0, idProfe;
        //char *bloque;
        //string contenido;
        vector<MatrizSala> vectorSalida;
        MatrizSala *salaAnalizada;

        /*  for(int h = 0; h < vectorSalas.size(); h++){
            
            salaAnalizada = new MatrizSala(vectorSalas[h]);
            cout<<"salaAnalizada "<< salaAnalizada->getIdSala()<<endl;
            while(salaAnalizada->getBloquesDisponibles()>0){
                for(i=0; i < vectorDisponibilidad.size(); i++){
                    DisponibilidadHoraria *matrizDisponibilidad = &vectorDisponibilidad[i];
                    int bloquesFreeDocente = matrizDisponibilidad->getCantidadBloquesLibres();
                    while(bloquesFreeDocente>0){
                        for(j=0; j<vectorDocentes.size(); j++){
                    
                        DocenteCurso *docente= &vectorDocentes[j];
                        if(docente->getIdProfe()==matrizDisponibilidad->getIdDocente()){ //OK
                                
                                //const char *codigo = docente->getCodigoCurso().c_str();
                                                    
                                for(k=0; k<BLOQUES; k++){
                                    for(l=0; l< DIAS; l++){
                                        if(matrizDisponibilidad->getDisponibilidad(k,l) && salaAnalizada->consultarDispDia(k,l)
                                        && docente->getBloquesTotalesRamo()>0){ 
                                            contenido = docente->getCodigoCurso();
                                            cout<<"todo ok"<<endl;
                                            salaAnalizada->insertarBloque(k,l,contenido); 
                                            cout<<"todo ok"<<endl;
                                            matrizDisponibilidad->setDisponibilidad(k,l,false);
                                            docente->setBloquesTotalesRamo();                                        
                                            count++;
                                            cout<<"count"<<count<<endl;
                                        }
                                
                                    }
                                }
                        }
                    }
                    bloquesFreeDocente--;
                    }
            }
            }
            
            vectorSalida.push_back(*salaAnalizada);
            delete salaAnalizada;
        }

        */
        
        
        MatrizSala *salita;
        for(int g=0; g<vectorSalida.size(); g++){
            salita = &vectorSalida[g];
            for(int i=0; i<BLOQUES; i++){
                for(int j=0; j< DIAS; j++){
                    cout<<salita->getIdSala()<<" "<<salita->getBloque(i,j)<<endl;
                }
            }
        }
        escribirExcel(vectorSalida, vectorDias); // Genera el excel de Salida Horario.xlsx
    

    }else {
        std::cerr << std::endl << "Argumentos insuficientes o incorrectos" << std::endl;
        std::cerr << std::endl << argv[0] << " -d Docentes.xlsx -c Cursos.xlsx -s Salas.xlsx" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}