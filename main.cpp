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
    vector<DocenteCurso> vectorDocenteCurso = llenarVectorDocenteCurso();
    // vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHoraria();
    // vector<HorarioSala> vectorHorarioSala = llenarVectorHorarioSala();

    MPI_Init(NULL, NULL);

    int procesos;
    int proceso;

    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    MPI_Comm_size(MPI_COMM_WORLD, &procesos);

    if(proceso == 0){
        //Se recorre una vez por cada objeto DocenteCurso
        for(int i = 0; i < vectorDocenteCurso.size(); i++){
            if(//Si empieza con INF recorre desde el primer lab hasta el ultimo)

            else if(//Si no empieza con INF recorre desde el primer m hasta el ultimo){

            }

        }
    }

    if(proceso == 1){
        
    }

    if(proceso == 2){
        
    }

    MPI_Finalize();
    return 0;
}