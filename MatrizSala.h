#ifndef MATRIZSALA_H
#define MATRIZSALA_H
#define BLOQUES 7
#define DIAS 6
#define VACIA "EMPTY"
#define NOONE "-"
#define OFERTA 39
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "docente_curso.h"

using namespace std;

class MatrizSala {

    private:
        
        std::string idSala;
        bool full;
        std::string matrizHorario[BLOQUES][DIAS];
        int bloquesDisponibles;       
    

    public:

    MatrizSala();
    //MatrizSala(DocenteCurso Docente);
    MatrizSala(std::string id, int matriz[BLOQUES][DIAS]);
    virtual ~MatrizSala();

    void setIdSala(string id);
    string getIdSala();
    
    int getBloquesDisponibles();
    
    void updateAvailability(bool availability);
    void mostrarMatriz();
    int getBloquesPorDia(int dia);
    
    
};

#endif /* MATRIZSALA_H */
