#include <iostream>
#include <xlsxio_read.h>
#include <vector>
#include <string>
#include "xlsxwriter.h"
#include "funciones.h"
#include "MatrizSala.h"

using namespace std;

int main(){
    
    vector<string> vectorSalas;
    /*
    *                       ESTE VECTOR LO USARÁN? SINO, LO METO EN LA FUNCION EscribirExcel
    *  */
    vector<string> vectorDias = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};

    vector<MatrizSala> vectorMatricesConSalas;

    char * bloque= "bloque";
            
    const char* nombreArchivoSalas = "Salas.xlsx";
    vectorSalas = llenarArregloSalas(nombreArchivoSalas);

     for(int i=1; i < vectorSalas.size(); i++){
        MatrizSala *salita = new MatrizSala(vectorSalas[i]);
        for(int f=0; f<5; f++){
            salita->insertarBloque(f,0,bloque);
        }
        vectorMatricesConSalas.push_back(*salita);
    }

    escribirExcel(vectorMatricesConSalas, vectorDias);

    return 0;
}