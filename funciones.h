#pragma once
#include <vector>
#include "docente_curso.h"
<<<<<<< HEAD
#include "disponibilidad_horaria.h"
=======
#include "MatrizSala.h"
#define BLOQUES 7
>>>>>>> Pipe---ClaseMatrizSala

using namespace std;

vector<DocenteCurso> llenarVectorDocenteCurso();

<<<<<<< HEAD
//Se modificó
vector<DisponibilidadHoraria> llenarVectorDisponibilidadHoraria();

bool retornaBooleano(string);
void mostrarMatrizDisponibilidad(vector<vector<bool>>);

//Se crearon
vector<vector<bool>> retornaMatrizPorHoja(int);
vector<int> retornaVectorIdDocente();
=======
void escribirExcel(vector<MatrizSala> vectorMatricesConSalas, vector<string> dias);
vector<std::string> llenarArregloSalas(const char* nombreArchivoSalas);
void mostrarArregloSalas(vector<string> vectorSalas);
void reservarBloque(int bloque,int dia,int idProfe,std::string idRamo, MatrizSala* sala);

>>>>>>> Pipe---ClaseMatrizSala
