#pragma once
#include <vector>
#include "docente_curso.h"
#include "disponibilidad_horaria.h"
#include "MatrizSala.h"
#define BLOQUES 7


using namespace std;

vector<DocenteCurso> llenarVectorDocenteCurso();
vector<DocenteCurso> llenarVectorDocenteCursoNew(const char*);

void mostrarVectorDocenteCurso(vector<DocenteCurso>);

vector<DisponibilidadHoraria> llenarVectorDisponibilidadHorariaNew(const char*, vector<string>);

bool retornaBooleano(string);
void mostrarMatrizDisponibilidad(vector<vector<bool>>);

vector<vector<bool>> retornaMatrizPorHoja(int);
vector<int> retornaVectorIdDocente();

//Matrices con Salas para Escritura en Excel
vector<MatrizSala> crearVectorConSalasVacias(vector<string> );
void escribirExcel(vector<MatrizSala>, vector<string>);

//Vector con las Salas leidas del xlsx
vector<std::string> llenarArregloSalas(const char* );
void mostrarArregloSalas(vector<string> );

int bloquesDisponiblesEnMatrizBooleana(vector<vector<bool>>);
char * crearNombreConcatenado(string&, int&);
