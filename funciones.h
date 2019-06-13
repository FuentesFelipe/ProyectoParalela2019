#pragma once
#include <vector>
#include "docente_curso.h"
#include "disponibilidad_horaria.h"

using namespace std;

vector<DocenteCurso> llenarVectorDocenteCurso();

vector<DisponibilidadHoraria> llenarVectorDisponibilidadHoraria();

void mostrarMatrizDisponibilidad(vector<vector<bool>>);

vector<vector<bool>> retornaMatrizPorHoja(int);

vector<int> retornaVectorIdDocente();