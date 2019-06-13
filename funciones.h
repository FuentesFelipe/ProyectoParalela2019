#pragma once
#include <vector>
#include "DocenteCurso.h"
#include "DisponibilidadHoraria.h"

using namespace std;

vector<DocenteCurso> llenarVectorDocenteCurso();

vector<DisponibilidadHoraria> llenarVectorDisponibilidadHoraria();

void mostrarMatrizDisponibilidad(vector<vector<bool>>);
void mostrarMatrizHorario(vector<vector<string>>);

vector<vector<bool>> retornaMatrizPorHoja(int);

vector<int> retornaVectorIdDocente();