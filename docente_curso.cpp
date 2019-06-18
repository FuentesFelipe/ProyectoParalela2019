#include "docente_curso.h"
#include <iostream>

using namespace std;

DocenteCurso::DocenteCurso(string codigo_curso, int id_docente, int bloques_disponibles){
    string codigoCurso = codigo_curso + "-";
    codigoCurso+= static_cast<ostringstream*>( &(ostringstream() << id_docente) )->str();
    this->codigo_curso = codigoCurso;
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

int DocenteCurso::getIdProfe(){
    return this->id_docente;
}

int DocenteCurso::getBloquesTotalesRamo(){
    return this->bloques_disponibles;
}

void DocenteCurso::setBloquesTotalesRamo(){
    this->bloques_disponibles = this->bloques_disponibles -1 ;
}

std::string DocenteCurso::getCodigoCurso(){
    return this->codigo_curso;
}
