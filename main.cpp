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
    vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHoraria();
    vector<HorarioSala> vectorHorarioSala = llenarVectorHorarioSala();

    for(int i = 0; i < vectorDocenteCurso.size(); i++){
        vectorDocenteCurso[i].mostrarDatos();
        cout << endl;
    }

    for(int i = 0; i < vectorDisponibilidad.size(); i++){
        vectorDisponibilidad[i].mostrarDatos();
        cout << endl;
    }


    for(int i = 0; i < vectorHorarioSala.size(); i++){
        vectorHorarioSala[i].mostrarDatos();
        cout << endl;
    }    

    return 0;
}