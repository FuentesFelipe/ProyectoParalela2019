#include "funciones.h"
#include <iostream>
#include <string>
#include <xlsxio_read.h>
#include "xlsxwriter.h"

using namespace std;

vector<DocenteCurso> llenarVectorDocenteCurso(){
    vector<DocenteCurso> vectorDocenteCurso; //Vector a ser llenado con los registros del archivo Cursos
    DocenteCurso *docenteCursoAuxiliar = NULL; //Puntero que se utilizará como auxiliar para llenar vectorDocenteCurso;

    xlsxioreader archivoCursos; //Se inicia el tipo de dato para leer archivos
    
    archivoCursos = xlsxioread_open("Cursos.xlsx");

    char* celda; //Puntero que recorrerá las celdas del archivo Cursos.xlsx
    xlsxioreadersheet hojaArchivoCursos;

    //Se abre la hoja "Secciones"
    hojaArchivoCursos = xlsxioread_sheet_open(archivoCursos, "Secciones", XLSXIOREAD_SKIP_EMPTY_ROWS);
    
    //Declaración de funciones a utilizar en las iteraciones
    int numFila = 1;//Se utiliza para no leer la primera fila porque no posee datos útiles
    int numColumna;//Se utiliza para saber en que columna está posicionado el puntero *celda
    
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

vector<DisponibilidadHoraria> llenarVectorDisponibilidadHoraria(){
    vector<DisponibilidadHoraria> vectorDisponibilidadHoraria;
    DisponibilidadHoraria *disponibilidadHorariaAuxiliar = NULL;
    
    //Vectores con datos 
    vector<int> vectorIdDocentes = retornaVectorIdDocente();
    vector<vector<vector<bool>>> vectorMatricesPorDia;
    
    for(int i = 0; i < 6; i++)
        vectorMatricesPorDia.push_back(retornaMatrizPorHoja(i));
    
    
    int id_docente_auxiliar;
    
    //Vectores auxiliares para ser llenados y almacenados
    vector<vector<bool>> *matrizDisponibilidadAuxiliar = NULL; 
    vector<bool> *vectorDisponibilidadAuxiliar = NULL;

    //Este for recorre una vez por cada docente
    for(int i = 0; i < vectorIdDocentes.size(); i++){
        id_docente_auxiliar = vectorIdDocentes[i];

        matrizDisponibilidadAuxiliar = new vector<vector<bool>>(); //Matriz disp cada docente       

        //Este for recorre los días de la semana
        for(int j = 0; j < 6; j++){

            vectorDisponibilidadAuxiliar = new vector<bool>();
            
            //Este for recorre la disponibilidad de cada día 
            for(int k = 0; k < vectorMatricesPorDia[j][i].size(); k++){
                vectorDisponibilidadAuxiliar->push_back(vectorMatricesPorDia[j][i][k]); 
            }

            matrizDisponibilidadAuxiliar->push_back(*vectorDisponibilidadAuxiliar);
             
            vectorDisponibilidadAuxiliar = NULL;          
        }  
        disponibilidadHorariaAuxiliar = new DisponibilidadHoraria(id_docente_auxiliar, *matrizDisponibilidadAuxiliar);
        
        vectorDisponibilidadHoraria.push_back(*disponibilidadHorariaAuxiliar);

        disponibilidadHorariaAuxiliar = NULL;
        matrizDisponibilidadAuxiliar = NULL;
    }    
    
    return vectorDisponibilidadHoraria;
}

vector<vector<bool>> retornaMatrizPorHoja(int dia){
    vector<string> vectorDias = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
    
    xlsxioreader archivoDocentes; //Se inicia el tipo de dato para leer archivos
    
    archivoDocentes = xlsxioread_open("Docentes.xlsx");
    
    char* celda; //Puntero que recorrerá las celdas del archivo Docentes.xlsx
    
    xlsxioreadersheet hojaArchivoDocentes;

    //Se abre la hoja especificada por parámetro
    hojaArchivoDocentes = xlsxioread_sheet_open(archivoDocentes, vectorDias[dia].c_str(), XLSXIOREAD_SKIP_EMPTY_ROWS);

    //Declaración de funciones a utilizar en las iteraciones
    int numFila = 1;//Se utiliza para no leer la primera fila porque no posee datos útiles
    int numColumna;//Se utiliza para saber en que columna está posicionado el puntero *celda
        
    string disponibilidad;//Se utiliza para cambiar de DISPONIBLE/NODISPONIBLE a 0s y 1s

    vector<vector<bool>> matrizDisponibilidad;
    vector<bool> *vectorDisponibilidad = NULL;

    while(xlsxioread_sheet_next_row(hojaArchivoDocentes)){
                numColumna = 1;
                if(numFila > 1)
                    vectorDisponibilidad = new vector<bool>();
                
                while((celda = xlsxioread_sheet_next_cell(hojaArchivoDocentes)) != NULL){
                    if(numFila > 1 && numColumna > 3){
                        disponibilidad = celda;
                        
                        if(disponibilidad == "DISPONIBLE"){
                            vectorDisponibilidad->push_back(1);
                        }   
                        else                  
                        {
                            vectorDisponibilidad->push_back(0);
                        }   
                        
                    }    
                    numColumna++;
                }

                if(numFila > 1){
                    matrizDisponibilidad.push_back(*vectorDisponibilidad);
                    vectorDisponibilidad = NULL; 
                }
                   
                numFila++;
            }
    xlsxioread_sheet_close(hojaArchivoDocentes);

    return matrizDisponibilidad;    
}

vector<int> retornaVectorIdDocente(){
    vector<int> vectorIdDocente;

    xlsxioreader archivoDocentes; //Se inicia el tipo de dato para leer archivos
    
    archivoDocentes = xlsxioread_open("Docentes.xlsx");

    char* celda; //Puntero que recorrerá las celdas del archivo Cursos.xlsx
    xlsxioreadersheet hojaArchivoDocentes;

    //Se abre la hoja "Secciones"
    hojaArchivoDocentes = xlsxioread_sheet_open(archivoDocentes, "Lunes", XLSXIOREAD_SKIP_EMPTY_ROWS);
    
    //Declaración de funciones a utilizar en las iteraciones
    int numFila = 1;//Se utiliza para no leer la primera fila porque no posee datos útiles
    int numColumna;//Se utiliza para llevar saber en que columna está posicionado el puntero *celda
    
    int id_docente_auxiliar;
    string char_a_string;//Se utiliza para parsear las celdas de char* a String
    
    while(xlsxioread_sheet_next_row(hojaArchivoDocentes)){
                numColumna = 1;
                while((celda = xlsxioread_sheet_next_cell(hojaArchivoDocentes)) != NULL){
                    if(numFila != 1){
                        //Se obtiene el id docente
                        if(numColumna == 1){
                            char_a_string = celda;
                            id_docente_auxiliar = stoi(char_a_string);    
                        }
                        free(celda);
                    }    
                    numColumna++;
                }

                if(numFila != 1){
                    vectorIdDocente.push_back(id_docente_auxiliar);
                }            
                numFila++;
            }
            xlsxioread_sheet_close(hojaArchivoDocentes);

    return vectorIdDocente;
}

bool retornaBooleano(string disponibilidad){
    bool valorDisponibilidad = false;
    if(disponibilidad == "DISPONIBLE")
        valorDisponibilidad = true;

    return valorDisponibilidad;
}

void mostrarMatrizDisponibilidad(vector<vector<bool>> vectorDisponibilidadHoraria){
    for(int i = 0; i < vectorDisponibilidadHoraria.size(); i++){
        for(int j = 0; j < vectorDisponibilidadHoraria[i].size(); j++){
            cout << vectorDisponibilidadHoraria[i][j] << "\t";
        }
        cout << endl;
    }
}

vector<MatrizSala> crearVectorConSalasVacias(vector<string> vectorSalas){

    vector<MatrizSala> vectorConSalas;
    for(int i = 0; i < vectorSalas.size(); i++){
        MatrizSala *salaIndividual = new MatrizSala(vectorSalas[i]);
        vectorConSalas.push_back(*salaIndividual);
    }

    return vectorConSalas;

}


void escribirExcel(vector<MatrizSala> vectorMatricesConSalas){
      /*
      * Función que crea el Excel de Salida y sus hojas.
      * 
      * @param vectorMatricesConSalas, el vector que contiene todas las salas rellenadas.
      * 
      * Recorre el arreglo, por cada sala se crea una hoja nueva y se escriben los
      * datos de la matrizSala en cada celda
      * 
      *  */
      vector<string> vectorDias = {"Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};

      lxw_workbook  *archivoExcel  = workbook_new("Horario.xlsx");
      for(int x = 0; x < vectorMatricesConSalas.size(); x++){

            //Capturamos una Sala
            MatrizSala *salaIndividual = &vectorMatricesConSalas[x]; 

            //Hoja Nueva para la Sala captura
            lxw_worksheet *worksheet = workbook_add_worksheet(archivoExcel, salaIndividual->getIdSala().c_str());

            // Iteración por filas "bloques"
            for (int i = 0; i < BLOQUES; i++)
            {
                worksheet_write_string(worksheet,0,i+1,vectorDias[i].c_str(), NULL);
                //worksheet_write_string(worksheet,i+1,0,strcat("BLOQUE ", "0" +i+1), NULL);

                // Iteración por columnas "Dias"
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

        //Fin
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
        hoja = xlsxioread_sheet_open(archivoSalas, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
        
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
