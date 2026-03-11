#pragma once

#pragma once
#include"Celda.h"
const int DIM = 9;
struct tTablero {
	int dimension;
	tCelda matriz[DIM][DIM];
};

void inicializaTablero(tTablero& t);
void inicializaTablero(tTablero& t, int d);

int dame_dimension(const tTablero& t);
tCelda dam_elem(const tTablero& t, int f, int c);

void pon_elemento(tTablero& t, int f, int c, tCelda celda);

