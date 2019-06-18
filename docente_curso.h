#pragma once
#include <string>
#include <sstream>

class DocenteCurso{
    private:
        std::string codigo_curso;
        int id_docente;
        int bloques_disponibles;
    
    public:
        DocenteCurso(std::string, int, int);
        ~DocenteCurso();
        void mostrarDatos();
        int getIdProfe();
        int getBloquesTotalesRamo();
        void setBloquesTotalesRamo();
        std::string getCodigoCurso();

};