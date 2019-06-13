#pragma once
#include <vector>
#include <string>

using namespace std;

class HorarioSalas{
    private:
        string nombre_sala;
        vector<vector<string>> matriz_horario;
    
    public:
        HorarioSalas(string, vector<vector<string>>);
        ~HorarioSalas();
        void mostrarDatos();
};