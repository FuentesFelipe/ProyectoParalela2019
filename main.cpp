#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>

#include "funciones.h"
#include "docente_curso.h"
#include "disponibilidad_horaria.h"

using namespace std;

int main(){
    vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHoraria();
    vector<DocenteCurso> vectorDocenteCurso = llenarVectorDocenteCurso();

    for(int i = 0; i < 10; i++){
        vectorDisponibilidad[i].mostrarDatos();
        cout << endl;
        vectorDocenteCurso[i].mostrarDatos();
        cout << endl;

    }
        
    
    

    return 0;
}