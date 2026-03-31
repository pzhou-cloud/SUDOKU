#pragma once
#include "Tablero.h";
#include <fstream>;
using namespace std;
struct tPosicion {
	int fila, columna;
};

struct tBloqueos {
	int cont;
	tPosicion bloqueadas[DIM * DIM];
};

struct tSudoku {
	tTablero tablero;
	int cont_numeros;
	tBloqueos celdas_bloqueadas;

};

void inicializaSudoku(tSudoku& s);
void carga_sudoku(ifstream& archivo, tSudoku& s);
int dame_dimension(const tSudoku& s);
tCelda dame_celda(const tSudoku s, int f, int c);

bool terminado(const tSudoku& s);
bool bloqueo(const tSudoku& s);
int dame_celda_bloqueadas(const tSudoku& s);
bool es_valor_posible(const tSudoku& s, int f, int c, int v);

bool pon_valor(tSudoku& s, int f, int c, int v);
bool quita_valor(tSudoku& s, int f, int c);
void reset(tSudoku& s);
void autocompleta(tSudoku& s);
int posibles_valores(tSudoku& s, int f, int c, int v); 
