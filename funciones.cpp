#include "funciones.h"
#include <iostream>
#include <string>
#include <xlsxio_read.h>

using namespace std;

vector<DocenteCurso> llenarVectorDocenteCurso(){
    vector<DocenteCurso> vectorDocenteCurso; //Vector a ser llenado con los registros del archivo Cursos
    DocenteCurso *docenteCursoAuxiliar = NULL; //Puntero que se utilizará como auxiliar para llenar el vectorxlsxioreader archivoCursos;

    xlsxioreader archivoCursos; //Se inicia el tipo de dato para leer archivos
    
    archivoCursos = xlsxioread_open("Cursos.xlsx");

    char* celda; //Puntero que recorrerá las celdas del archivo Cursos.xlsx
    xlsxioreadersheet hojaArchivoCursos;

    //Se abre la hoja "Secciones"
    hojaArchivoCursos = xlsxioread_sheet_open(archivoCursos, "Secciones", XLSXIOREAD_SKIP_EMPTY_ROWS);
    
    //Declaración de funciones a utilizar en las iteraciones
    int numFila = 1;//Se utiliza para no leer la primera fila porque no posee datos útiles
    int numColumna;//Se utiliza para llevar saber en que columna está posicionado el puntero *celda
    
    string codigo_curso_auxiliar;
    int id_docente_auxiliar;
    int bloques_disponibles_auxiliar;
    
    string char_a_string;//Se utiliza para parsear las celdas de char* a String
    
    while(xlsxioread_sheet_next_row(hojaArchivoCursos)){
                numColumna = 1;
                while((celda = xlsxioread_sheet_next_cell(hojaArchivoCursos)) != NULL){
                    if(numFila != 1){
                        //Se obtiene el código del curso
                        if(numColumna == 1){
                            codigo_curso_auxiliar = celda;  
                        }

                        //Se obtiene el id docente
                        if(numColumna == 3){
                            char_a_string = celda;
                            id_docente_auxiliar = stoi(char_a_string);    
                        }

                        //Se obtiene los bloques del profesor
                        if(numColumna == 6){
                            char_a_string = celda;
                            bloques_disponibles_auxiliar = stoi(char_a_string);    
                        } 
                        free(celda);
                    }    
                    numColumna++;
                }

                if(numFila != 1){
                    DocenteCurso *docenteCursoAuxiliar = new DocenteCurso(codigo_curso_auxiliar, id_docente_auxiliar, bloques_disponibles_auxiliar);
                    vectorDocenteCurso.push_back(*docenteCursoAuxiliar);
                    docenteCursoAuxiliar = NULL;
                }            
                numFila++;
            }
            xlsxioread_sheet_close(hojaArchivoCursos);

    return vectorDocenteCurso;
}