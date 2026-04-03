#pragma once
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
	tCelda dame_celda(const tSudoku s, int f, int c) {
}

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
	
	return nombre_temporal(s, f, c, v) && !esta_valor_en_fila(s, f, v) &&
	!esta_valor_en_columna(s, c, v) && !esta_valor_en_bloque(s, f, c, v);
}

bool nombre_temporal(const tSudoku& s, int f, int c, int v){
	return  es_vacia(s.tablero.matriz[f][c]) && (v > 0 && v <= 9);
}

bool esta_valor_en_fila(const tSudoku& s, int f, int v){

	bool ok = false;
	int c = 0;

	while(ok == false && c < DIM){
		if(s.tablero.matriz[f][c].valor == v){
			ok = true;
		}
		c++;
	}

	return ok;
}

bool esta_valor_en_columna(const tSudoku& s, int c, int v){

	bool ok = false;
	int f = 0;

	while(ok == false && f < DIM){
		if(s.tablero.matriz[f][c].valor == v){
			ok = true;
		}
		f++;
	}

	return ok;
}

bool esta_valor_en_bloque(const tSudoku& s, int f, int c, int v){

	bool ok = false;
	int f_esquina_bloque = f / 3 * 3;
	int c_esquina_bloque = c / 3 * 3;

	while(!ok && f_esquina_bloque < f_esquina_bloque + 3){

		while(!ok && c_esquina_bloque < c_esquina_bloque + 3){
			if(s.tablero.matriz[f][c].valor == v){
				ok = true;
			}
			c_esquina_bloque++;
		}
		f_esquina_bloque++;
	}

	return ok;
}




bool pon_valor(tSudoku& s, int f, int c, int v) {

	bool ok = false;

	if (es_valor_posible(s, f, c, v)) {

		pon_valor(s.tablero.matriz[f][c], v); 
		pon_ocupada(s.tablero.matriz[f][c]); 
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
	
	for(int i = 0; i < DIM; i++){
		for(int j= 0; j < DIM; j++){

			quita_valor(s, i, j);
		}
	}

	//TODO: Mirar donde guardamos el número original de celdas ocupadas
	s.cont_numeros = 999;
	s.celdas_bloqueadas.cont = 0;


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
