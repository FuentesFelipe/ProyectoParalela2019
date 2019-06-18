#include "disponibilidad_horaria.h"
#include "funciones.h"
#include <iostream>

using namespace std;

DisponibilidadHoraria::DisponibilidadHoraria(int id_docente, int bloquesTotales, vector<vector<bool>> matriz_disponibilidad){
    this->id_docente = id_docente;
    this->matriz_disponibilidad = matriz_disponibilidad;
    this->bloquesDisponibles = bloquesTotales;
}

DisponibilidadHoraria::DisponibilidadHoraria(int idProfe){
    vector<bool> periodoSemanal;
    this->id_docente = idProfe;
    this->bloquesDisponibles = 0;
    for(int i=0; i < BLOQUES ; i++){
        for(int j=0; j<DIAS; j++){
            periodoSemanal.push_back(false);
        }
        this->matriz_disponibilidad.push_back(periodoSemanal);
    }
}

DisponibilidadHoraria::~DisponibilidadHoraria(){}

void DisponibilidadHoraria::mostrarDatos(){
    cout << "Id docente: " << this->id_docente << endl;
    cout << "Matriz disponibilidad: " << endl;
    cout << "disponibilidad " << this->bloquesDisponibles<<endl;
    for(int i = 0; i < BLOQUES; i++){
        for(int j = 0; j < DIAS; j++){
            cout << this->matriz_disponibilidad[i][j]<<" ";
        }
        cout<<endl;
    }
}

int DisponibilidadHoraria::getIdDocente(){
    return this->id_docente;
};

vector<vector<bool>> DisponibilidadHoraria::getMatriz(){
    return this->matriz_disponibilidad;
}

void DisponibilidadHoraria::setDisponibilidad(int row, int col, bool disponibilidad){
    this->matriz_disponibilidad[row][col] = disponibilidad;
    if(disponibilidad)
       this->bloquesDisponibles = this->bloquesDisponibles + 1; 
    else
        this->bloquesDisponibles = this->bloquesDisponibles - 1;
}

bool DisponibilidadHoraria::getDisponibilidad(int row ,int col){
    return this->matriz_disponibilidad[row][col];
}

int DisponibilidadHoraria::getCantidadBloquesLibres(){
    return this->bloquesDisponibles;
}