#pragma once
#include "Sudoku.h"
const int MAX_LISTA = 2;
struct tListaSudokus {
	int cont;
	int capacidad;
	tSudoku** sudokus; // lo usais como si fuera un array
	//Sobreescritura operador[] para indexar directamente la lista
	// siendo tListaSudokus ls; 
	// ls[índice] seria equivalente a *(-ls.sudokus[indice]))
	tSudoku& operator[](int indice) {
		return *sudokus[indice];
	};

};
typedef int arrValores[MAX_VALORES];
void inicializaListaSudokus(tListaSudokus& ls);
void destruyeListaSudokus(tListaSudokus& ls);
int dame_num_elem(tListaSudokus& ls);
tSudoku dame_sudoku(tListaSudokus& ls, int i);
void redimensionar(tListaSudokus& ls, int nueva_capacidad);
void numero_posibles_valores(tSudoku& s, arrValores av);

bool operator==(tSudoku& s1, tSudoku& s2);
bool operator<(tSudoku& s1, tSudoku& s2);
