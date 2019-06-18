#pragma once
#include <vector>

using namespace std;

class DisponibilidadHoraria{
    private:
        int id_docente;
        int bloquesDisponibles;
        vector<vector<bool>> matriz_disponibilidad;
    
    public:
        DisponibilidadHoraria(int,int, vector<vector<bool>>);
        DisponibilidadHoraria(int);
        ~DisponibilidadHoraria();
        void mostrarDatos();
        int getIdDocente();
        bool getDisponibilidad(int,int);
        void setDisponibilidad(int,int,bool);
        
        vector<vector<bool>> getMatriz();
        int getCantidadBloquesLibres();
};