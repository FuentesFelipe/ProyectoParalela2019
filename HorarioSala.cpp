#include "HorarioSala.h"
#include "funciones.h"
#include <iostream>

using namespace std;

HorarioSala::HorarioSala(string nombre_sala, vector<vector<string>> matriz_horario){
    this->nombre_sala = nombre_sala;
    this->matriz_horario = matriz_horario;
}

HorarioSala::HorarioSala(string nombre_sala){
    this->nombre_sala = nombre_sala;
}

HorarioSala::~HorarioSala(){}

void HorarioSala::mostrarDatos(){
    cout << "Nombre sala: " << this->nombre_sala << endl;
    cout << "Matriz horario: " << endl;
    mostrarMatrizHorario(this->matriz_horario);
}

bool HorarioSala::esLAB(){
    string primerosTresChar = "";
    bool esLAB = false;
    for(int i = 0; i < 3; i++){
        primerosTresChar += this->nombre_sala[i];
    }

    if(primerosTresChar == "LAB")
        esLAB = true;

    return esLAB;
}

vector<vector<string>> HorarioSala::retornaMatrizHorario(){
    return this->matriz_horario;
}

void HorarioSala::llenarBloque(string identificadorDocente, int bloque, int dia){
    this->matriz_horario[bloque][dia] = identificadorDocente;
}

string HorarioSala::retornaNombreSala(){
    return this->nombre_sala;
}