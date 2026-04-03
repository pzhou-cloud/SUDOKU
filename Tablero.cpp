
#pragma once
#include "Tablero.h"

void inicializaTablero(tTablero& t) {
	t.dimension = 0;
}
void inicializaTablero(tTablero& t, int d) {
	t.dimension = d;
}
int dame_dimension(const tTablero& t) {
	return t.dimension;
}
tCelda dame_elem(const tTablero& t, int f, int c) {
	return t.matriz[f][c];

}

void pon_elemento(tTablero& t, int f, int c, tCelda celda) {

	t.matriz[f][c] = celda;

}