#pragma once
#include <vector>
#include "docente_curso.h"
#include "disponibilidad_horaria.h"

using namespace std;

vector<DocenteCurso> llenarVectorDocenteCurso();

//Se modificó
vector<DisponibilidadHoraria> llenarVectorDisponibilidadHoraria();

bool retornaBooleano(string);
void mostrarMatrizDisponibilidad(vector<vector<bool>>);

//Se crearon
vector<vector<bool>> retornaMatrizPorHoja(int);
vector<int> retornaVectorIdDocente();