#pragma once
#include <vector>

using namespace std;

class DisponibilidadHoraria{
    private:
        int id_docente;
        vector<vector<bool>> matriz_disponibilidad;
    
    public:
        DisponibilidadHoraria(int, vector<vector<bool>>);
        ~DisponibilidadHoraria();
        void mostrarDatos();
        int retornaIdDocente();
        vector<vector<bool>> retornaMatrizDisponiblidad();
};