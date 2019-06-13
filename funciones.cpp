#include "funciones.h"
#include <iostream>
#include <string>
#include <xlsxio_read.h>
#include "xlsxwriter.h"

using namespace std;

char * crearNombreConcatenado(string& idCurso, int& idProfe){
    
    char *buf = strcpy(buf,(idCurso+= "-" + idProfe).c_str());
    return buf;
    delete []buf;
}

vector<DocenteCurso> llenarVectorDocenteCursoNew(const char* nombreArchivo){

    /*
    *   Remodelación función de lectura del excel Cursos y creación del vector con Cursos
    *   Recibe el nombre del archivo y retorna un vector con objetos de la clase DocenteCurso
    *   
    *   @param nombreArchivo: nombre del excel
    * 
    *  */
    
    xlsxioreader archivoCursos;
    vector<DocenteCurso> vectorDocenteCursos;
    archivoCursos = xlsxioread_open(nombreArchivo);

    if((archivoCursos = xlsxioread_open(nombreArchivo)) == NULL){
        cout << "No se ha podido abrir el archivo." << endl;
    } else{

        char* celda;                                                    //Puntero a las celdas del Excel
        string idRamo;                                                  //Almacena el id del Curso
        int idProfe;                                                    //Almacena el id del Profesor
        int bloques;                                                    //Almacena la cantidad de Bloques del ramo
        int i;
        DocenteCurso *docente;                                          //Puntero a un objeto de la Clase DocenteCurso
        xlsxioreadersheet hoja = xlsxioread_sheet_open(archivoCursos, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
        xlsxioread_sheet_next_row(hoja);                                //Nos saltamos la primera fila
        while(xlsxioread_sheet_next_row(hoja)){                         //Mientras queden profes por leer    
            celda = xlsxioread_sheet_next_cell(hoja);                   
            idRamo = celda;                                             //Guardamos el ID del ramo
            i=1;                                                        //Variable para llevar el control de las columnas
            while(celda = xlsxioread_sheet_next_cell(hoja)){            //Mientras queden celdas en la fila del Docente
                    if(i==2){
                        idProfe= stoi(celda);                           //Guardamos el Id del profesor como entero
                    }
                    if(i==5){
                        bloques = stoi(celda);                          //Guardamos los bloques del ramo como entero
                    }
                    i++;                                                            
                    free(celda);
            }
            docente = new DocenteCurso(idRamo,idProfe,bloques);         //Creamos un docente
            vectorDocenteCursos.push_back(*docente);                    //Se inserta en el vector de Objetos Docentes
        }

        xlsxioread_sheet_close(hoja);
        xlsxioread_close(archivoCursos);
    }
    return vectorDocenteCursos;
}

void mostrarVectorDocenteCurso(vector<DocenteCurso> vectorDocenteCurso){
    DocenteCurso *docente;
    int i;
    for(i=0; i<vectorDocenteCurso.size();i++){
        docente = &vectorDocenteCurso[i];
        cout<<"IDCURSO "<<docente->getCodigoCurso()
        <<" IDPROFE "<<docente->getIdProfe()
        <<" bloques "<<docente->getBloquesTotalesRamo()
        <<endl;
    }
}

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
    int bloquesTotalesPorCurso;
    
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

                        //Se obtiene los bloques totales por curso
                        if(numColumna == 6){
                            char_a_string = celda;
                            bloquesTotalesPorCurso = stoi(char_a_string);    
                        } 
                        free(celda);
                    }    
                    numColumna++;
                }

                if(numFila != 1){
                    DocenteCurso *docenteCursoAuxiliar = new DocenteCurso(codigo_curso_auxiliar, id_docente_auxiliar, bloquesTotalesPorCurso);
                    vectorDocenteCurso.push_back(*docenteCursoAuxiliar);
                    docenteCursoAuxiliar = NULL;
                }            
                numFila++;
            }
            xlsxioread_sheet_close(hojaArchivoCursos);

    return vectorDocenteCurso;
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
    int bloquesTotales;
    string disponibilidad;//Se utiliza para cambiar de DISPONIBLE/NODISPONIBLE a 0s y 1s

    vector<vector<bool>> matrizDisponibilidad;
    vector<bool> *vectorDisponibilidad = NULL;

    while(xlsxioread_sheet_next_row(hojaArchivoDocentes)){
                bloquesTotales =0;
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

    for(int i = 0; i < DIAS; i++){
        for(int j = 0; j < BLOQUES; j++){
            cout << vectorDisponibilidadHoraria[i][j]<<" ";
        }
        cout<<endl;
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


void escribirExcel(vector<MatrizSala> vectorMatricesConSalas, vector<string> vectorDias){
      /*
      * Función que crea el Excel de Salida y sus hojas.
      * 
      * @param vectorMatricesConSalas, el vector que contiene todas las salas rellenadas.
      * 
      * Recorre el arreglo, por cada sala se crea una hoja nueva y se escriben los
      * datos de la matrizSala en cada celda
      * 
      *  */

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
                for (int j = 0; j < DIAS; j++)
                {   // Inserta el Bloque en el formato IDCURSO-IDPROFE en su celda correspondiente
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

int bloquesDisponiblesEnMatrizBooleana(vector<vector<bool>> matrizBooleana){
    int bloques = 0;
    int i,j;
    for(i=0; i <matrizBooleana.size(); i++){
        vector<bool> vectorBoolPorDia = matrizBooleana[i];
        for(j=0; j< vectorBoolPorDia.size(); j++){
            if (!vectorBoolPorDia[j]){
                bloques++;
            }
        }
    }
    return bloques;
}

vector<DisponibilidadHoraria> llenarVectorDisponibilidadHorariaNew(const char* nombreArchivoDocentes, vector<string> vectorDias){

    /*
    *   Funcion que lee el archivo de Docentes y retorna
    *   un vector con objetos DisponibilidadHoraria
    *   
    *   @param nombreArchivoDocentes recibirá el nombre del excel
    *   
    *   Etapa 1 : Comienza cargando el archivo
    *   Etapa 2 : Si se lee correctamente, se declaran las variables necesarias
    *   Etapa 3 :   
    *   
    *  */ 
    xlsxioreader archivoDocentes;
    vector<DisponibilidadHoraria> vectorConObjetos;
        
    if((archivoDocentes = xlsxioread_open(nombreArchivoDocentes)) == NULL){
        cout << "No se ha podido abrir el archivo." << endl;
    }
    else{

        vector<vector<vector<bool>>> vectorConDisponibilidades;
        vector<bool> vectorBloquesPorDia;
        
        int profe;
        int dia;
        int columna;
        char* celda;
        xlsxioreadersheet hoja,sheet;
        sheet = xlsxioread_sheet_open(archivoDocentes, NULL, XLSXIOREAD_SKIP_EMPTY_ROWS);
        xlsxioread_sheet_next_cell(sheet);
        while(xlsxioread_sheet_next_row(sheet)){
                celda = xlsxioread_sheet_next_cell(sheet);
                DisponibilidadHoraria *nueva = new DisponibilidadHoraria(stoi(celda));
                vectorConObjetos.push_back(*nueva);
        }
        xlsxioread_sheet_close(sheet);
        for(dia=0; dia<DIAS; dia++){
            hoja = xlsxioread_sheet_open(archivoDocentes,vectorDias[dia].c_str() , XLSXIOREAD_SKIP_EMPTY_ROWS);
            profe=0;
            DisponibilidadHoraria *profeEvaluado = NULL;
            xlsxioread_sheet_next_row(hoja);
            while (xlsxioread_sheet_next_row(hoja)){
                profeEvaluado = &vectorConObjetos[profe];
                for(columna =0; columna<3; columna++)
                    celda = xlsxioread_sheet_next_cell(hoja);

                while ((celda = xlsxioread_sheet_next_cell(hoja)) != NULL){
                    if(retornaBooleano(celda)){
                        profeEvaluado->setDisponibilidad(columna - 3,dia,true);
                    }
                    columna++;  
                }
                vectorConObjetos[profe] = (*profeEvaluado);
                profe++;
            }
        }

        xlsxioread_sheet_close(hoja);
        xlsxioread_close(archivoDocentes);

    }
    return vectorConObjetos;
}