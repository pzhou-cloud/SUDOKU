#pragma once
#include "Sudoku.h";


void inicializaSudoku(tSudoku& s) {
	s.cont_numeros = 0;
	s.celdas_bloqueadas.cont = 0;
}

void carga_sudoku(ifstream& archivo, tSudoku& s) {

	int value;
	archivo >> s.tablero.dimension;

	for (int i = 0; i < s.tablero.dimension; i++) {
		for (int j = 0; j < s.tablero.dimension; j++) {

			archivo >> value;

			if (value == 0) {
				s.tablero.matriz[i][j].estado = VACIA;
			}
			else {
				s.tablero.matriz[i][j].estado = ORIGINAL;
				s.tablero.matriz[i][j].valor = value;
				s.cont_numeros++;
			}



		}

	}

}

int dame_dimension(const tSudoku& s) {
	return s.tablero.dimension;
}

tCelda dame_celda(const tSudoku s, int f, int c) {
	return s.tablero.matriz[f][c];
}

bool terminado(const tSudoku& s) {
	return s.cont_numeros == s.tablero.dimension * s.tablero.dimension;
}

bool bloqueo(const tSudoku& s) {
	return s.celdas_bloqueadas.cont != 0;
}

int dame_celda_bloqueadas(const tSudoku& s) {
	return s.celdas_bloqueadas.cont; 

}
bool es_valor_posible(const tSudoku& s, int f, int c, int v) {
	bool ok = false; 
	if (s.tablero.matriz[f][c].estado != OCUPADA && s.tablero.matriz[f][c].estado != ORIGINAL) {
		s.tablero.matriz[f][c].valor = v;
		ok = true;
	}// falta

}

void pon_valor(tSudoku& s, int f, int c, int v) {
	if (es_valor_posible(s, f, c, v)) {

		s.tablero.matriz[f][c].valor = v;

		//Actualizar celdas bloqueadas
		s.celdas_bloqueadas.cont++;
		tPosicion posicion;
		posicion.fila = f;
		posicion.columna = c;
		s.celdas_bloqueadas.bloqueadas[s.celdas_bloqueadas.cont] = posicion;

		//Aumentar valor celdas no vacías
		ok = true;
	}


}
void quita_valor(tSudoku& s, int f, int c) {

}
void reset(tSudoku& s);
void autocompleta(tSudoku& s);



