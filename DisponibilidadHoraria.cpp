#include "DisponibilidadHoraria.h"
#include "funciones.h"
#include <iostream>

using namespace std;

DisponibilidadHoraria::DisponibilidadHoraria(int id_docente, vector<vector<bool>> matriz_disponibilidad){
    this->id_docente = id_docente;
    this->matriz_disponibilidad = matriz_disponibilidad;
}

DisponibilidadHoraria::DisponibilidadHoraria(int id_docente){
    this->id_docente = id_docente;
}
DisponibilidadHoraria::~DisponibilidadHoraria(){}

void DisponibilidadHoraria::mostrarDatos(){
    cout << "Id docente: " << this->id_docente << endl;
    cout << "Matriz disponibilidad: " << endl;
    mostrarMatrizDisponibilidad(this->matriz_disponibilidad);
}

int DisponibilidadHoraria::retornaIdDocente(){
    return this->id_docente;
}

void DisponibilidadHoraria::setDisponibilidad(int columna,int dia,bool disponibilidad){
    this->matriz_disponibilidad[columna][dia] = disponibilidad;
}

vector<vector<bool>> DisponibilidadHoraria::retornaMatrizDisponiblidad(){
    return this->matriz_disponibilidad;
}