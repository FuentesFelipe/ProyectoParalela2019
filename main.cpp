#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>

#include "funciones.h"
#include "docente_curso.h"
#include "disponibilidad_horaria.h"

using namespace std;

int main(int argc, char *argv[]){
    /*
    *   Main con llamadas a funciones para comprobar funcionamiento de funciones globales
    *   
    *   El nombre de los archivos entrarán como argumento del main
    * 
    *  */

    const char* nombreArchivo = "Salas.xlsx";                       //Solo de prueba
    vector<string> vectorSalas;                                     //
    vectorSalas = llenarArregloSalas(nombreArchivo);                //Se crea el vector con salas
    mostrarArregloSalas(vectorSalas);                               //Lectura para comprobacion

    
    vector<MatrizSala> vectorConSalasVacias = crearVectorConSalasVacias(vectorSalas); 
    
    escribirExcel(vectorConSalasVacias); // Genera el excel de Salida Horario.xlsx

    vector<DisponibilidadHoraria> vectorPrueba = llenarVectorDisponibilidadHoraria();

    for(int i = 0; i < vectorPrueba.size(); i++)
        vectorPrueba[i].mostrarDatos();
    

    return 0;
}