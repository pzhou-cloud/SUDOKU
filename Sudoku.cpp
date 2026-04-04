#include "Sudoku.h"

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

tCelda dame_celda(const tSudoku& s, int f, int c) {
	return s.tablero.matriz[f][c];
}

bool terminado(const tSudoku& s) {
	return s.cont_numeros == s.tablero.dimension * s.tablero.dimension;
}

bool bloqueo(const tSudoku& s) {
	return s.celdas_bloqueadas.cont != 0;
}

int dame_num_celda_bloqueadas(const tSudoku& s){
	return s.celdas_bloqueadas.cont;

}

void dame_celda_bloqueada(const tSudoku& s, int p, int& f, int& c) {
	f = s.celdas_bloqueadas.bloqueadas[p].fila; 
	c = s.celdas_bloqueadas.bloqueadas[p].columna;
}

bool nombre_temporal(const tSudoku& s, int f, int c, int v) {
	return  es_vacia(s.tablero.matriz[f][c]) && (v >= 1 && v <= 9);
}

bool esta_valor_en_fila(const tSudoku& s, int f, int v) {

	bool ok = false;
	int c = 0;

	while (ok == false && c < DIM) {
		if (s.tablero.matriz[f][c].valor == v) {
			ok = true;
		}
		c++;
	}

	return ok;
}

bool esta_valor_en_columna(const tSudoku& s, int c, int v) {

	bool ok = false;
	int f = 0;

	while (ok == false && f < DIM) {
		if (s.tablero.matriz[f][c].valor == v) {
			ok = true;
		}
		f++;
	}

	return ok;
}

bool esta_valor_en_bloque(const tSudoku& s, int f, int c, int v) {

	bool ok = false;
	int f_esquina_bloque = f / 3 * 3;
	int c_esquina_bloque = c / 3 * 3;
	int i = f_esquina_bloque;
	int j = c_esquina_bloque;

	while (!ok && i < f_esquina_bloque + 3) {

		j = c_esquina_bloque;

		while (!ok && j < c_esquina_bloque + 3) {
			if (s.tablero.matriz[i][j].valor == v) {
				ok = true;
			}
			j++;
		}
		i++;
	}

	return ok;
}

bool es_valor_posible(const tSudoku& s, int f, int c, int v) {

	return (nombre_temporal(s, f, c, v) && !esta_valor_en_fila(s, f, v) &&
		!esta_valor_en_columna(s, c, v) && !esta_valor_en_bloque(s, f, c, v));

}


void busca_celdas_bloqueadas(tSudoku& s) {

	s.celdas_bloqueadas.cont = 0;

	for (int f = 0; f < DIM; f++) {
		for (int c = 0; c < DIM; c++) {
			if (posibles_valores(s, f, c) == 0) {
				s.celdas_bloqueadas.bloqueadas[s.celdas_bloqueadas.cont].fila = f;
				s.celdas_bloqueadas.bloqueadas[s.celdas_bloqueadas.cont].columna = c;
				s.celdas_bloqueadas.cont++;
			}

		}
	}
}


bool pon_valor(tSudoku& s, int f, int c, int v) {

	bool ok = false;

	if (es_valor_posible(s, f, c, v)) {

		pon_valor(s.tablero.matriz[f][c], v);
		pon_ocupada(s.tablero.matriz[f][c]);
		s.cont_numeros++;

		busca_celdas_bloqueadas(s);

		ok = true;
	}

	return ok;
}
bool quita_valor(tSudoku& s, int f, int c) {
	bool ok = false;
	if (!es_vacia(dame_celda(s, f, c)) && !es_original(dame_celda(s, f, c)) && f >= 0 && f < 9) {

		tCelda celda = dame_celda(s, f, c);
		pon_vacia(celda);
		s.tablero.matriz[f][c].valor = 0; 

		busca_celdas_bloqueadas(s);
		s.cont_numeros--; 
		ok = true;
	}
	return ok;

}
void reset(tSudoku& s) {

	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {

			quita_valor(s, i, j);
		}
	}

	//TODO: Mirar donde guardamos el número original de celdas ocupadas
	s.cont_numeros = 999;
	s.celdas_bloqueadas.cont = 0;


}
void autocompleta(tSudoku& s) {
	int v = 1;
	while (v < 9) {
		for (int i = 0; i < DIM; i++) {
			for (int j = 0; j < DIM; j++) {
				if (posibles_valores(s, i, j) == 1) {
					pon_valor(s, i,j,v);
				}

			}

		}
		v++;
	}
}

int posibles_valores(tSudoku& s, int f, int c) {
	int v = 1;
	int num = 0;

	if (es_vacia(s.tablero.matriz[f][c])) {
		while (v <= 9) {
			if (es_valor_posible(s, f, c, v)) { 
				num++;
			}
			v++;
		}
	}


	return num;
}
