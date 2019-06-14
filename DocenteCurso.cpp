#include "DocenteCurso.h"
#include <iostream>

using namespace std;

DocenteCurso::DocenteCurso(string codigo_curso, int id_docente, int bloques_disponibles){
    this->codigo_curso = codigo_curso;
    this->id_docente = id_docente;
    this->bloques_disponibles = bloques_disponibles;
}

DocenteCurso::~DocenteCurso(){
}

void DocenteCurso::mostrarDatos(){
    cout << "Código curso: " << this->codigo_curso << endl;
    cout << "Id docente: " << this->id_docente << endl;
    cout << "Bloques disponiles: " << this->bloques_disponibles << endl;
}

bool DocenteCurso::esINF(){
    string primerosTresChar = "";
    bool esINF = false;
    for(int i = 0; i < 3; i++){
        primerosTresChar += this->codigo_curso[i];
    }

    if(primerosTresChar == "INF")
        esINF = true;

    return esINF;
}

int DocenteCurso::retornaBloquesDisponibles(){
    return this->bloques_disponibles; 
}