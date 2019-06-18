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
        char* matrizHorario[BLOQUES][DIAS];
        int bloquesDisponibles;       
    

    public:

    MatrizSala(std::string);
    
    virtual ~MatrizSala();

    void setIdSala(string);
    string getIdSala();
    
    int getBloquesDisponibles();
    void mostrarMatriz();
    void insertarBloque(int , int , string);
    
    //Ingresa un día de forma entera (0 = lunes, 1 = martes...)
    // Retorna la cantidad de bloques disponibles en ese día
    int getBloquesDisponiblesPorDia(int);
    char* getBloque(int, int); 

    bool consultarDispDia(int,int);
    
    
};

#endif /* MATRIZSALA_H */
