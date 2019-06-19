#include "DisponibilidadHoraria.h"
#include "funciones.h"
#include <iostream>

using namespace std;

DisponibilidadHoraria::DisponibilidadHoraria(int id_docente, vector<vector<bool>> matriz_disponibilidad){
    this->id_docente = id_docente;
    this->matriz_disponibilidad = matriz_disponibilidad;
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

vector<vector<bool>> DisponibilidadHoraria::retornaMatrizDisponiblidad(){
    return this->matriz_disponibilidad;
}