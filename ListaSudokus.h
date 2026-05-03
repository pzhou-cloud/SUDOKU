#pragma once
#include "Sudoku.h"

const int MAX_LISTA = 2;

struct tListaSudokus {
	int cont;
	int capacidad;
	tSudoku** sudokus;
	tSudoku& operator[](int indice) {
		return *sudokus[indice];
	};

};

typedef int arrValores[MAX_VALORES];

void inicializaListaSudokus(tListaSudokus& ls);
void destruyeListaSudokus(tListaSudokus& ls);
int dame_num_elem(const tListaSudokus& ls);
const tSudoku& dame_sudoku(const tListaSudokus& ls, int i);
void redimensionar(tListaSudokus& ls, int nueva_capacidad);
void numero_posibles_valores(const tSudoku& s, arrValores av);

bool operator==(const tSudoku& s1, const tSudoku& s2);
bool operator<(const tSudoku& s1, const tSudoku& s2);
void insertar(tListaSudokus& ls, tSudoku& s);
void eliminar(tListaSudokus& ls, int pos);
void mostrar_lista(const tListaSudokus& ls);