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
        char* matrizHorario[BLOQUES][DIAS];
        int bloquesDisponibles;       
    

    public:

    MatrizSala(std::string);
    
    virtual ~MatrizSala();

    void setIdSala(string id);
    string getIdSala();
    
    int getBloquesDisponibles();
    void mostrarMatriz();
    void insertarBloque(int bloque, int dia, char* profeRamo);
    
    //Ingresa un día de forma entera (0 = lunes, 1 = martes...)
    // Retorna la cantidad de bloques disponibles en ese día
    int getBloquesPorDia(int dia);

    char* getBloque(int row, int col); 
    
    
};

#endif /* MATRIZSALA_H */
