#pragma once
#include <vector>
#include <string>

using namespace std;

class HorarioSala{
    private:
        string nombre_sala;
        vector<vector<string>> matriz_horario;
    
    public:
        HorarioSala(string, vector<vector<string>>);
        HorarioSala(string);
        ~HorarioSala();
        void mostrarDatos();
        bool esLAB();
        vector<vector<string>> retornaMatrizHorario();
        void llenarBloque(string, int, int);
        string retornaNombreSala();
};