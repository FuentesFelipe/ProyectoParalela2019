#pragma once
#include <string>

class DocenteCurso{
    private:
        std::string codigo_curso;
        int id_docente;
        int bloques_disponibles;
    
    public:
        DocenteCurso(std::string, int, int);
        ~DocenteCurso();
        void mostrarDatos();
        bool esINF();
        int retornaBloquesDisponibles();
        void restaBloquesDisponibles();
        std::string retornaIdentificador();
        int retornaIdDocente();
};