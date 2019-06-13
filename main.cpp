#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>

#include "funciones.h"
#include "DocenteCurso.h"
#include "DisponibilidadHoraria.h"
#include "HorarioSalas.h"

using namespace std;

int main(){
    vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHoraria();
    vector<DocenteCurso> vectorDocenteCurso = llenarVectorDocenteCurso();

    vector<vector<string>> matrizSala;
    vector<string> stringPrueba;
    
    for(int i = 0; i < 3; i++)
        stringPrueba.push_back("Disponible");
    for(int i = 0; i < 3; i++)
        matrizSala.push_back(stringPrueba);


    HorarioSalas sala("M1-301", matrizSala);

    sala.mostrarDatos();
    

    return 0;
}