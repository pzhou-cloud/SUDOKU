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
				s.cont_numeros++;
			}
			s.tablero.matriz[i][j].valor = value;



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
bool es_valor_posible(tSudoku& s, int f, int c, int v) {
	bool ok = false;
	if (es_vacia(s.tablero.matriz[f][c]) && v > 0 && v >= 9) { // pq 0 es nada

		ok = true;
	}
	return ok;
}

bool pon_valor(tSudoku& s, int f, int c, int v) {

	bool ok = false;

	if (es_valor_posible(s, f, c, v)) {

		s.tablero.matriz[f][c].valor = v;

		//Actualizar celdas bloqueadas
		
		tPosicion posicion;
		posicion.fila = f;
		posicion.columna = c;
		s.celdas_bloqueadas.bloqueadas[s.celdas_bloqueadas.cont] = posicion;
		s.celdas_bloqueadas.cont++;

		//Aumentar valor celdas no vacías
		ok = true;
	}

	return ok;
}
bool quita_valor(tSudoku& s, int f, int c) {
	bool ok = false; 
	if (!es_vacia(dame_celda(s, f, c)) && !es_original(dame_celda(s, f, c)) && f > 0 && f <= 9) {

		tCelda celda = dame_celda(s, f, c);
		pon_vacia(celda);
		s.celdas_bloqueadas.cont--; 
		ok = true; 
		//problema para el futuro
	}
	return ok; 

}
void reset(tSudoku& s) {
	for (int i = 1; i <= s.celdas_bloqueadas.cont; i++) {
		for (int j = 1; j <= s.celdas_bloqueadas.cont; j++) {
			quita_valor(s, i, j); 
		}
	}


}
void autocompleta(tSudoku& s) {
	int v=1; 
	while (v < 9) {
		for (int i = 1; i < DIM; i++) {
			for (int j = 1; i < DIM; j++) {
				if (posibles_valores(s, i, j, v) == 1) {
					pon_valor(s.tablero.matriz[i][j], v); 
				}

			}

		}
		v++; 
	}
}

int posibles_valores(tSudoku& s, int f, int c, int v) {
	int num=0; 
	while (num < 9) {
		if (es_valor_posible(s, f, c, v)) {
			num++;
		}
		num++; 
	}

	return num; 
}
