#pragma once
#include "Tablero.h"
#include <iostream>
#include <fstream>
using namespace std;

const int MAX_VALORES = 9;
struct tPosicion {
	int fila, columna;
};

struct tBloqueos {
	int cont;
	tPosicion bloqueadas[DIM * DIM];
};

typedef struct {
	bool posible;
	int celdas_que_afectan;
}tValor;

typedef struct {
	int nFilas;
	int nColumnas;
	tValor valores[DIM][DIM][MAX_VALORES];
}tValores;

typedef struct {
	tTablero tablero;
	int cont_numeros;
	tBloqueos celdas_bloqueadas;
	tValores valores_celda;

}tSudoku;

void inicializaSudoku(tSudoku& s);
void carga_sudoku(ifstream& archivo, tSudoku& s);
int dame_dimension(const tSudoku& s);
tCelda dame_celda(const tSudoku& s, int f, int c);

bool terminado(const tSudoku& s);

//Sesión 4:
bool bloqueo(const tSudoku& s);
int dame_num_celda_bloqueadas(const tSudoku& s);
void dame_celda_bloqueada(const tSudoku& s, int p, int& f, int& c);
void actualiza_celdas_bloqueadas(tSudoku& s);
void inserta_celda_bloqueada(tSudoku& s, const tPosicion& pos);
void elimina_celda_bloqueada(tSudoku& s, const tPosicion& pos);
void elimina_celdas_bloqueadas(tSudoku& s, int f, int c);
bool es_valor_posible(const tSudoku& s, int f, int c, int v);

bool pon_valor(tSudoku& s, int f, int c, int v);
bool quita_valor(tSudoku& s, int f, int c);
void reset(tSudoku& s);
void autocompleta(tSudoku& s);
int posibles_valores(const tSudoku& s, int f, int c); 

