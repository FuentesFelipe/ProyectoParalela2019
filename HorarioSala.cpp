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

vector<vector<string>> HorarioSala::retornaMatrizHorario(){
    return this->matriz_horario;
}

void HorarioSala::llenarBloque(string identificadorDocente, int bloque, int dia){
    if(this->matriz_horario[bloque][dia] == "Disponible"){
        this->matriz_horario[bloque][dia] = identificadorDocente;
    }

}