#include <iostream>
#include <xlsxio_read.h>
#include <vector>
#include <string>
#include "xlsxwriter.h"

using namespace std;

int main(){
    xlsxioreader archivoSalas;
    vector<string> vectorSalas;
    string nombreSala;

    if((archivoSalas = xlsxioread_open("Salas.xlsx")) == NULL){
        cout << "No se ha podido abrir el archivo." << endl;
        return 1;
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

    lxw_workbook  *archivoExcel  = workbook_new("archivo.xlsx");

    for(int i = 0; i < vectorSalas.size(); i++){
        workbook_add_worksheet(archivoExcel, vectorSalas[i].c_str());       

    }
    
    
    


    workbook_close(archivoExcel);
    

    return 0;
}