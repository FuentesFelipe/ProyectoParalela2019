#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>

#include "funciones.h"
#include "docente_curso.h"
#include "disponibilidad_horaria.h"

using namespace std;

int main(){
    vector<DisponibilidadHoraria> vectorPrueba = llenarVectorDisponibilidadHoraria();

    for(int i = 0; i < vectorPrueba.size(); i++)
        vectorPrueba[i].mostrarDatos();
    
    

    return 0;
}