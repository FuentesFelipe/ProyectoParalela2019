#include "MatrizSala.h"
#include "funciones.h"
#include <iostream>

using namespace std;

MatrizSala::MatrizSala(std::string edificioSala){
    /*
    *   Constructor que recibe el formato "M1-X0Y"
    *   y llena su matriz de disponibilidad con vacios "EMPTY"
    *   
    *  */
    this->idSala = edificioSala;
    this->bloquesDisponibles = OFERTA; //OFERTA = 39 constante de bloques permitidos por semana

    for (int i = 0; i < BLOQUES; i++){
        
        for (int j = 0; j < DIAS -1 ; j++){
                
                this->matrizHorario[i][j] = (VACIA);
        }       
    }
    for (int k = 0; k<8; k++){ // Iteración para rellenar el día sábado
        if(k<4){
            
            this->matrizHorario[k][5] = (VACIA);
        } 
        else{
            this->matrizHorario[k][5] = (NOONE); //Marca los días no disponibles
        }
        
    }
}

MatrizSala::~MatrizSala(){
}


void MatrizSala::setIdSala(string id){
    this->idSala=id;
}

string MatrizSala::getIdSala(){
    return this->idSala;
}
int MatrizSala::getBloquesDisponiblesPorDia(int dia){
    int disponibles=0;
    try{
        if(dia<6){
            int i;
            for (i = 0; i < BLOQUES; i++)
            {
                if(this->matrizHorario[i][dia]==(VACIA)){
                   disponibles++; 
                }
            }
        }

    }catch (...){
        return disponibles;
    }
    return disponibles;
}

int MatrizSala::getBloquesDisponibles(){
    return this->bloquesDisponibles;
}

void MatrizSala::mostrarMatriz(){
    cout <<endl<<" Mostrando disponibilidad de la sala "<< this->idSala<<endl<<endl;
    cout << "BLQ/DIA  LUNES   MARTES  MIERCOLES  JUEVES  VIERNES   SABADO"<<endl;
    for (int i = 0; i < BLOQUES; i++)
    {
        cout<<"BLOQUE "<<i+1<<" ";
        for (int j = 0; j < DIAS; j++)
        {
            cout <<this->matrizHorario[i][j]<<"    ";
        }
         cout << endl;
    }
    cout<<endl<<this->bloquesDisponibles<<" Bloques disponibles"<<endl<<endl;
}

void MatrizSala::insertarBloque(int bloque, int dia, string profeRamo){
    
   if(dia<DIAS && bloque<BLOQUES){                               // Primera validación
       if(dia==5 && bloque>=4){                         // Validación para el Sábado

       } else{
            this->matrizHorario[bloque][dia]=constToCharArray(profeRamo);
            this->bloquesDisponibles = this->bloquesDisponibles - 1;
       }
   }
}

char* MatrizSala::getBloque(int row, int col){
    return this->matrizHorario[row][col];
} 

bool MatrizSala::consultarDispDia(int row,int col){
    if(this->matrizHorario[row][col]==VACIA){
        return true;
    } else{
        return false;
    }
}



