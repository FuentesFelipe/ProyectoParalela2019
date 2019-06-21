#pragma once
#include <vector>
#include "DocenteCurso.h"
#include "DisponibilidadHoraria.h"
#include "HorarioSala.h"
#define BLOQUES 7
#define DIAS 6


using namespace std;

char* obtener_entrada(char**, int, char*);
void mostrarMatrizDisponibilidad(vector<vector<bool>>);

void mostrarMatrizHorario(vector<vector<string>>);

vector<DocenteCurso> llenarVectorDocenteCurso(const char*);
vector<DocenteCurso> llenarVectorDocenteCursoNew(const char*);

vector<vector<bool>> retornaMatrizPorHoja(int);
vector<int> retornaVectorIdDocente(const char*);
vector<vector<bool>> cambiarColumnasPorFilas(vector<vector<bool>>&);
vector<DisponibilidadHoraria> llenarVectorDisponibilidadHoraria(const char*);

vector<vector<string>> llenarMatrizHorarioDisponible();
vector<HorarioSala> llenarVectorHorarioSala(const char*);
vector<std::string> llenarArregloSalas(const char*);
vector<DisponibilidadHoraria> llenarVectorDisponibilidadHorariaNew(const char*, vector<string>);

bool hayCuatroBloquesSeguidos(string, int, int, vector<vector<string>>);

vector<vector<bool>> retornaMatrizPorDocente(vector<DisponibilidadHoraria>, int);
bool tieneDisponibilidad(int, int, vector<vector<bool>>);

void escribirExcel(vector<HorarioSala>);

bool retornaBooleano(string);
vector<HorarioSala> crearVectorConSalasVacias(vector<string>);