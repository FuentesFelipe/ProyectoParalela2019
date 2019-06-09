#include "MatrizSala.h"
#include <iostream>

using namespace std;

MatrizSala::MatrizSala(){
    this->full = false;
    this->idSala = VACIA;
    this->bloquesDisponibles = OFERTA;

    for (int i = 0; i < BLOQUES; i++){
        
        for (int j = 0; j < DIAS -1 ; j++){
                
                this->matrizHorario[i][j] = (VACIA);
        }       
    }
    for (int k = 0; k<8; k++){
        if(k<4){
            this->matrizHorario[k][5] = (VACIA);
        } else
        {
            this->matrizHorario[k][5] = (NOONE);
        }
        
    }
}

MatrizSala::~MatrizSala(){
}

/*MatrizSala::MatrizSala(DocenteCurso Docente){

    for (int i = 0; i < BLOQUES; i++){
        
        for (int j = 0; j < DIAS; j++){

            this->matrizHorario[i][j] = (VACIA);

        }        
    }
    // POR WEAR
} */

MatrizSala::MatrizSala(std::string id, int matriz[BLOQUES][DIAS]){
    
    try {
        this->idSala = id;
        MatrizSala();
        for (int i = 0; i < BLOQUES; i++)
        {
            for (int j = 0; j < DIAS; j++)
            {
                //Llenado... por definir
            }
            
        }

    } catch (...){
        MatrizSala();
    }

}

void MatrizSala::setIdSala(string id){
    this->idSala=id;
}

int MatrizSala::getBloquesPorDia(int dia){
    int disponibles=0;
    try{
        if(dia<6){
            int i;
            for (i = 0; i < BLOQUES; i++)
            {
                if(this->matrizHorario[i][dia].compare(VACIA)==0){
                   disponibles++; 
                }
            }
            
        }

    }catch (...){
        disponibles = 0;
    }
    return disponibles;
}

int MatrizSala::getBloquesDisponibles(){
    return this->bloquesDisponibles;
}

void MatrizSala::mostrarMatriz(){
    cout << "BLQ/DIA  LUNES   MARTES  MIERCOLES  JUEVES  VIERNES   SABADO"<<endl;
    int dias =0;
    for (int i = 0; i < BLOQUES; i++)
    {
        cout<<"BLOQUE "<<i+1<<" ";
        for (int j = 0; j < DIAS; j++)
        {
            cout <<this->matrizHorario[i][j]<<"    ";
            dias++;
        }
         cout << endl;
    }
    cout<<endl<<this->bloquesDisponibles<<" Bloques disponibles"<<dias<<endl;
}



