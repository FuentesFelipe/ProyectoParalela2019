#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>

#include "funciones.h"
#include "docente_curso.h"

using namespace std;

int main(){
    
    vector<DocenteCurso> vectorDocenteCurso = llenarVectorDocenteCurso();

    for(int i = 0; i < vectorDocenteCurso.size(); i++){
        vectorDocenteCurso[i].mostrarDatos();
    }




    return 0;
}