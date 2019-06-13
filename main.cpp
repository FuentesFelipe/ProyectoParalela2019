#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>

#include "funciones.h"
#include "DocenteCurso.h"
#include "DisponibilidadHoraria.h"
#include "HorarioSala.h"

using namespace std;

int main(){
    vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHoraria();
    // vector<DocenteCurso> vectorDocenteCurso = llenarVectorDocenteCurso();

    // for(int i = 0; i < vectorDisponibilidad.size(); i++)
    //     vectorDisponibilidad[i].mostrarDatos();

    // for(int i = 0; i < vectorDocenteCurso.size(); i++)
    //     vectorDocenteCurso[i].mostrarDatos();


    vector<vector<string>> matrizSala;
    vector<string> stringPrueba;
    
    for(int i = 0; i < 3; i++)
        stringPrueba.push_back("Disponible");
    for(int i = 0; i < 3; i++)
        matrizSala.push_back(stringPrueba);


    HorarioSala sala("M1-301", matrizSala);

    sala.mostrarDatos();
    

    return 0;
}