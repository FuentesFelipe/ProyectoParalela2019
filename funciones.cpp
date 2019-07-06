#include "funciones.h"
#include <iostream>
#include <string>
#include <xlsxio_read.h>
#include "xlsxwriter.h"

using namespace std;

char* obtener_entrada(char** matriz, int largo, char* identificador) {
    char* archivo = NULL;
    int i = 0, k = 0;

    if (largo > 0) {
        for (i = 0; i < largo; i++) {
            if (strcmp(identificador, matriz[i]) == 0) {
                k = i + 1;
                archivo = (char *) calloc(strlen(matriz[k]) + 1, sizeof (char));

                snprintf(archivo, strlen(matriz[k]) + 1, "%s", matriz[k]);
                break;
            }
        }
    }

    return archivo;
}

void mostrarMatrizDisponibilidad(vector<vector<bool>> vectorDisponibilidadHoraria){
    for(int i = 0; i < vectorDisponibilidadHoraria.size(); i++){
        for(int j = 0; j < vectorDisponibilidadHoraria[i].size(); j++){
            cout << vectorDisponibilidadHoraria[i][j] << "\t";
        }
        cout << endl;
    }
}

void mostrarMatrizHorario(vector<vector<string>> vectorHorarioSala){
    for(int i = 0; i < vectorHorarioSala.size(); i++){
        for(int j = 0; j < vectorHorarioSala[i].size(); j++){
            cout << vectorHorarioSala[i][j] << "\t";
        }
        cout << endl;
    }
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

vector<DocenteCurso> llenarVectorDocenteCurso(const char* nombreArchivo){
    vector<DocenteCurso> vectorDocenteCurso; //Vector a ser llenado con los registros del archivo Cursos
    DocenteCurso *docenteCursoAuxiliar = NULL; //Puntero que se utilizará como auxiliar para llenar vectorDocenteCurso;

    xlsxioreader archivoCursos; //Se inicia el tipo de dato para leer archivos
    
    archivoCursos = xlsxioread_open(nombreArchivo);

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
                    //Transformamos horas pedagógicas a Bloques
                    if(bloques_disponibles_auxiliar>1) // Cazamos las horas pedagógicas distintas a 1
                        bloques_disponibles_auxiliar = bloques_disponibles_auxiliar/2;

                    DocenteCurso *docenteCursoAuxiliar = new DocenteCurso(codigo_curso_auxiliar, id_docente_auxiliar, bloques_disponibles_auxiliar);
                    
                    vectorDocenteCurso.push_back(*docenteCursoAuxiliar);
                    delete(docenteCursoAuxiliar);
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
                        free(celda);
                    }    
                    numColumna++;
                }

                if(numFila > 1){
                    matrizDisponibilidad.push_back(*vectorDisponibilidad);
                    delete(vectorDisponibilidad);
                    vectorDisponibilidad = NULL; 
                }
                   
                numFila++;
            }
    xlsxioread_sheet_close(hojaArchivoDocentes);

    return matrizDisponibilidad;    
}

vector<int> retornaVectorIdDocente(const char* nombreArchivo){
    vector<int> vectorIdDocente;

    xlsxioreader archivoDocentes; //Se inicia el tipo de dato para leer archivos
    
    archivoDocentes = xlsxioread_open(nombreArchivo);

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

vector<vector<bool>> cambiarColumnasPorFilas(vector<vector<bool>> &matrizATransformar){
    vector<bool> *punteroColumna = NULL;
    vector<vector<bool>> matrizTransformada;

    int columna = 0;
    int fila = 0;

    while(columna < 7){
        punteroColumna = new vector<bool>();
        fila = 0;

        if(columna < 4){
            while(fila < 6){
                punteroColumna->push_back(matrizATransformar[fila][columna]);
                fila++;
            }
        }

        else if(4 <= columna){
            while(fila < 5){
                punteroColumna->push_back(matrizATransformar[fila][columna]);
                fila++;
            }
        }

        matrizTransformada.push_back(*punteroColumna);
        delete(punteroColumna);
        punteroColumna = NULL;

        columna++;
    }

    matrizATransformar = matrizTransformada;

    return matrizATransformar;    

}


vector<DisponibilidadHoraria> llenarVectorDisponibilidadHoraria(const char* nombreArchivo){
    vector<DisponibilidadHoraria> vectorDisponibilidadHoraria;
    DisponibilidadHoraria *disponibilidadHorariaAuxiliar = NULL;
    
    //Vectores con datos 
    vector<int> vectorIdDocentes = retornaVectorIdDocente(nombreArchivo);
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
        *matrizDisponibilidadAuxiliar = cambiarColumnasPorFilas(*matrizDisponibilidadAuxiliar); 
        disponibilidadHorariaAuxiliar = new DisponibilidadHoraria(id_docente_auxiliar, *matrizDisponibilidadAuxiliar);
        
        vectorDisponibilidadHoraria.push_back(*disponibilidadHorariaAuxiliar);

        delete(disponibilidadHorariaAuxiliar);
        delete(matrizDisponibilidadAuxiliar);

        disponibilidadHorariaAuxiliar = NULL;
        matrizDisponibilidadAuxiliar = NULL;
    }    
    
    return vectorDisponibilidadHoraria;
}

vector<vector<string>> llenarMatrizHorarioDisponible(){
    int columna = 0;
    int fila = 0;

    vector<string> *punteroColumna = NULL;
    vector<vector<string>> Matriz;

    while(columna < 7){
        punteroColumna = new vector<string>();
        fila = 0;

        if(columna < 4){
            while(fila < 6){
                punteroColumna->push_back("Disponible");
                fila++;
            }
        }

        else if(4 <= columna){
            while(fila < 5){
                punteroColumna->push_back("Disponible");
                fila++;
            }
        }
        
        Matriz.push_back(*punteroColumna);
        delete(punteroColumna);
        punteroColumna = NULL;

        columna++;
    }

    return Matriz;
}


vector<HorarioSala> llenarVectorHorarioSala(const char* nombreArchivoSalas){
    vector<HorarioSala> vectorHorarioSala;
    HorarioSala *punteroHorarioSalaAuxiliar;
    
    string nombreSalaAuxiliar;

    xlsxioreader archivoSalas;
    archivoSalas = xlsxioread_open(nombreArchivoSalas);

    char* celda;
    xlsxioreadersheet hoja;
    hoja = xlsxioread_sheet_open(archivoSalas, "Sheet1", XLSXIOREAD_SKIP_EMPTY_ROWS);
    int numColumna;
    int numFila = 1;
    
    while (xlsxioread_sheet_next_row(hoja)){
        numColumna = 1;            
        while ((celda = xlsxioread_sheet_next_cell(hoja)) != NULL){
            if(numFila != 1){
                if(numColumna == 1){
                    nombreSalaAuxiliar = string(celda);
                }

                if(numColumna == 2){
                    nombreSalaAuxiliar += "-" + string(celda);
                }
                numColumna++;
            }
            free(celda);
        }

        if(numFila != 1){
            punteroHorarioSalaAuxiliar = new HorarioSala(nombreSalaAuxiliar, llenarMatrizHorarioDisponible());
            vectorHorarioSala.push_back(*punteroHorarioSalaAuxiliar);
            delete(punteroHorarioSalaAuxiliar);
            punteroHorarioSalaAuxiliar = NULL;
        }
        numFila++;
    }
    xlsxioread_sheet_close(hoja);
    xlsxioread_close(archivoSalas);  

    return vectorHorarioSala;

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

bool hayCuatroBloquesSeguidos(string identificadorDocente, int bloque, int dia, vector<vector<string>> matrizHorario){
    bool hayCuatroBloques = false;
    

    if(bloque > 3){
        int contadorBloques = 0;
        for(int i = bloque - 4; i < bloque; i++){
            if(matrizHorario[i][dia] == identificadorDocente){
                contadorBloques++;
            }
        }

        if(contadorBloques == 4)
            hayCuatroBloques  = true;
        else
            hayCuatroBloques  = false;
    }


    

    return hayCuatroBloques;
    
}

vector<vector<bool>> retornaMatrizPorDocente(vector<DisponibilidadHoraria> vectorDisponibilidad, int id_docente){
    for(int i = 0; i < vectorDisponibilidad.size(); i++){
        if(vectorDisponibilidad[i].retornaIdDocente() == id_docente)
            return vectorDisponibilidad[i].retornaMatrizDisponiblidad();
    }
}

bool tieneDisponibilidad(int bloque, int dia, vector<vector<bool>> matrizDisponibilidad){
    bool tieneDisponibilidad;

    if(matrizDisponibilidad[bloque][dia] == 1)
        tieneDisponibilidad = true;
    else
        tieneDisponibilidad = false;

    return tieneDisponibilidad;
}

void escribirExcel(vector<HorarioSala> vectorHorarioSala, const char* nombreArchivo){

    lxw_workbook  *archivoExcel  = workbook_new(nombreArchivo);

    vector<string> primeraFila = {"Bloques/Días", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
    vector<string> primeraColumna = {"1", "2", "3", "4", "5", "6", "7"};

    for(int i = 0; i < vectorHorarioSala.size(); i++){
        lxw_worksheet *hoja = workbook_add_worksheet(archivoExcel, vectorHorarioSala[i].retornaNombreSala().c_str());
        vector<vector<string>> matrizHorario = vectorHorarioSala[i].retornaMatrizHorario();

        for(int i = 0; i < primeraFila.size(); i++)
            worksheet_write_string(hoja, 0, i, primeraFila[i].c_str(), NULL);
        
        for(int j = 0; j < primeraColumna.size(); j++)
            worksheet_write_string(hoja, j+1, 0, primeraColumna[j].c_str(), NULL);

        for(int dia = 0; dia < 6; dia++){
            //No es sábado
            if(dia != 5){
                for(int bloque = 0; bloque < 7; bloque++){
                    worksheet_write_string(hoja, bloque + 1, dia + 1, matrizHorario[bloque][dia].c_str(), NULL);
                }
            }
            //Es sábado
            else{
                for(int bloque = 0; bloque < 4; bloque++){
                    worksheet_write_string(hoja, bloque + 1, dia + 1, matrizHorario[bloque][dia].c_str(), NULL);                    
                }
            }
        }   
    }
    
    
    workbook_close(archivoExcel);

}

bool retornaBooleano(string disponibilidad){
    bool valorDisponibilidad = false;
    if(disponibilidad == "DISPONIBLE")
        valorDisponibilidad = true;

    return valorDisponibilidad;
}

vector<HorarioSala> crearVectorConSalasVacias(vector<string> vectorSalas){

    vector<HorarioSala> vectorConSalas;
    for(int i = 0; i < vectorSalas.size(); i++){
        HorarioSala *salaIndividual = new HorarioSala(vectorSalas[i]);
        vectorConSalas.push_back(*salaIndividual);
    }

    return vectorConSalas;

}
