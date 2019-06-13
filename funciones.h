#pragma once
#include <vector>
#include "DocenteCurso.h"
#include "DisponibilidadHoraria.h"
#include "HorarioSala.h"

using namespace std;

void mostrarMatrizDisponibilidad(vector<vector<bool>>);

void mostrarMatrizHorario(vector<vector<string>>);

vector<DocenteCurso> llenarVectorDocenteCurso();

vector<vector<bool>> retornaMatrizPorHoja(int);
vector<int> retornaVectorIdDocente();
vector<DisponibilidadHoraria> llenarVectorDisponibilidadHoraria();

vector<HorarioSala> llenarVectorHorarioSala();
