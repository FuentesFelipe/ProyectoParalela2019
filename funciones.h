#pragma once
#include <vector>
#include "docente_curso.h"
#include "MatrizSala.h"
#define BLOQUES 7

using namespace std;

vector<DocenteCurso> llenarVectorDocenteCurso();

void escribirExcel(vector<MatrizSala> vectorMatricesConSalas, vector<string> dias);
vector<std::string> llenarArregloSalas(const char* nombreArchivoSalas);
void mostrarArregloSalas(vector<string> vectorSalas);
void reservarBloque(int bloque,int dia,int idProfe,std::string idRamo, MatrizSala* sala);

