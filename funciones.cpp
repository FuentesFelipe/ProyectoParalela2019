#include "funciones.h"
#include <iostream>
#include <string>
#include <xlsxio_read.h>
#include "xlsxwriter.h"

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


void escribirExcel(vector<MatrizSala> vectorMatricesConSalas, vector<string> dias){
      /*
      * Función que crea el Excel de Salida y sus hojas.
      * 
      * @param archivoExcel, puntero a Salida.xlsx (vacio)
      * @param vectorMatricesConSalas, el vector que contiene todas las salas rellenadas.
      * @param dias, vector con los días de la semana "lunes", "martes"... 
      * 
      *  */
      lxw_workbook  *archivoExcel  = workbook_new("Horario.xlsx");
      for(int x = 0; x < vectorMatricesConSalas.size(); x++){

            MatrizSala *salaIndividual = &vectorMatricesConSalas[x]; //Capturamos una Sala

            lxw_worksheet *worksheet = workbook_add_worksheet(
                                        archivoExcel, 
                                        salaIndividual->getIdSala().c_str());

            for (int i = 0; i < BLOQUES; i++)
            {
                worksheet_write_string(worksheet,0,i+1,dias[i].c_str(), NULL);
                //worksheet_write_string(worksheet,i+1,0,strcat("BLOQUE ", "0" +i+1), NULL);
                for (int j = 0; j < DIAS; j++)
                {
                    /*
                    *   Inserta el Bloque en el formato IDCURSO-IDPROFE en su celda correspondiente
                    *  */
                    worksheet_write_string(worksheet,i+1,j+1,salaIndividual->getBloque(i,j), NULL);
                } 
            } 
        } 
        workbook_close(archivoExcel);
}

vector<std::string> llenarArregloSalas(const char* nombreArchivoSalas){

         xlsxioreader archivoSalas;
         vector<string> vectorSalas;
         string nombreSala;
        if((archivoSalas = xlsxioread_open(nombreArchivoSalas)) == NULL){
            cout << "No se ha podido abrir el archivo." << endl;
          return vectorSalas;
        }
        else{
        char* celda;
        xlsxioreadersheet hoja;
        hoja = xlsxioread_sheet_open(archivoSalas, "NombreSalas", XLSXIOREAD_SKIP_EMPTY_ROWS);
        int numColumna;
        int numFila = 1;
        
        while (xlsxioread_sheet_next_row(hoja)){
            numColumna = 1;            
            while ((celda = xlsxioread_sheet_next_cell(hoja)) != NULL){
                if(numFila != 1){
                    if(numColumna == 1){
                        nombreSala = string(celda);
                    }

                    if(numColumna == 2){
                        nombreSala += "-" + string(celda);
                    }
                    numColumna++;
                }
                free(celda);
            }

            if(numFila != 1){
                vectorSalas.push_back(nombreSala);
            }
            numFila++;
        }
        xlsxioread_sheet_close(hoja);
        xlsxioread_close(archivoSalas);  
    }
    
}

void mostrarArregloSalas(vector<string> vectorSalas){
    for(int i=1; i < vectorSalas.size(); i++){
        cout<< vectorSalas[i]<<endl;
    }
}
