#include "HorarioSala.h"
#include "funciones.h"
#include <iostream>

using namespace std;

HorarioSala::HorarioSala(string nombre_sala, vector<vector<string>> matriz_horario){
    this->nombre_sala = nombre_sala;
    this->matriz_horario = matriz_horario;
}

HorarioSala::~HorarioSala(){}

void HorarioSala::mostrarDatos(){
    cout << "Nombre sala: " << this->nombre_sala << endl;
    cout << "Matriz horario: " << endl;
    mostrarMatrizHorario(this->matriz_horario);
}