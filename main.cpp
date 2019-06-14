#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>
#include <mpi.h>

#include "funciones.h"
#include "DocenteCurso.h"
#include "DisponibilidadHoraria.h"
#include "HorarioSala.h"

using namespace std;

int main(){

    MPI_Init(NULL, NULL);

    int procesos;
    int proceso;

    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    MPI_Comm_size(MPI_COMM_WORLD, &procesos);

    vector<DocenteCurso> vectorDocenteCurso = llenarVectorDocenteCurso();
    // vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHoraria();
    vector<HorarioSala> vectorHorarioSala = llenarVectorHorarioSala();

    if(proceso == 0){
        //Se recorre una vez por cada objeto DocenteCurso
        for(int i = 0; i < vectorDocenteCurso.size(); i++){
            //Se verifica que el DocenteCurso sea de INF
            if(vectorDocenteCurso[i].esINF()){
                int primerLab = 35;
                int ultimoLab = 40;

                //Se recorren todos los labs por cada DocenteCurso de INF    
                for(int j = primerLab; j <= ultimoLab; j++){

                    /*Acá necesito recorrer cada uno de los bloques de cada sala
                      en caso de que éste esté disponible mandar al proceso 1 que 
                      verifique si ya hay 4 bloques seguidos del mismo profe/curso, 
                      además de consultar al proceso 2 que verifique si el profesor 
                      tiene disponibilidad enviando por mensaje la posicion de la 
                      columna(dia) y de la fila (bloque), eśte debe retorna un 0 si no ó
                      un 1 si si. En caso de que la respuesta sea positiva por ambos procesos
                      cambiar de disponible a CODIGOCURSO/IDDOCENTE, luego se debe poner el 
                      bloque asignado como no disponible en disponibilidad (mismos indices
                      de consulta disponibilidad) y restar en uno los bloques disponibles.
                      Si bloques disponibles == 0  
                     */
                                        
                }
            }

            //Se verifica que el DocenteCurso no sea de INF
            else{
                int primeraSala = 0;
                int ultimaSala = 34;

                //Se recorren tdas las salas por cada DocenteCurso que no es de INF
                for(int j = primeraSala; j <= ultimaSala; j++){
                    /*Acá necesito recorrer cada uno de los bloques de cada sala
                      en caso de que éste esté disponible mandar al proceso 1 que 
                      verifique si ya hay 4 bloques seguidos del mismo profe/curso, 
                      además de consultar al proceso 2 que verifique si el profesor 
                      tiene disponibilidad enviando por mensaje la posicion de la 
                      columna(dia) y de la fila (bloque), eśte debe retorna un 0 si no ó
                      un 1 si si. En caso de que la respuesta sea positiva por ambos procesos
                      cambiar de disponible a CODIGOCURSO/IDDOCENTE, luego se debe poner el 
                      bloque asignado como no disponible en disponibilidad (mismos indices
                      de consulta disponibilidad) y restar en uno los bloques disponibles.
                      Si bloques disponibles == 0  
                     */                                        
                }

            }

        }
    }

    //Verifica que no hayan cuatro bloques del mismo curso/profe asignados
    if(proceso == 1){
        
    }

    //Verifica que el profe tenga disponibilidad, recibe indices retorna un bool
    if(proceso == 2){
        
    }

    MPI_Finalize();
    return 0;
}