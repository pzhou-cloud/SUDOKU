#include "ListaSudokus.h"
void inicializaListaSudokus(tListaSudokus& ls) {
	ls.cont = 0;
	ls.capacidad = MAX_LISTA;
	ls.sudokus = new tSudoku * [ls.capacidad];

}
void destruyeListaSudokus(tListaSudokus& ls) {
	for (int i = 0; i < ls.cont; i++) {
		destruir(ls[i]);
		delete ls.sudokus[i];
	}
	delete[] ls.sudokus;

}
int dame_num_elem(tListaSudokus& ls) {
	return ls.cont;
}
tSudoku dame_sudoku(tListaSudokus& ls, int i) {
	return ls[i];
}
void redimensionar(tListaSudokus& ls, int nueva_capacidad) {
	tSudoku** nuevo = new tSudoku * [nueva_capacidad];
	for (int i = 0; i < ls.cont; i++) {
		nuevo[i] = ls.sudokus[i];
	}
	delete[] ls.sudokus;
	ls.sudokus = nuevo;
	ls.capacidad = nueva_capacidad;
}
void numero_posibles_valores(tSudoku& s, arrValores av) {
	for (int i = 0; i < MAX_VALORES; i++) {
		av[i] = 0;
	}
	for (int f = 0; f < dame_dimension(s); f++) {
		for (int c = 0; c < dame_dimension(s); c++) {
			if (es_vacia(dame_celda(s, f, c))) {
				int num = posibles_valores(s, f, c);
				if (num > 0 && num <= MAX_VALORES) {
					av[num]++;
				}
			}


		}
	}
}

bool operator==(tSudoku& s1, tSudoku& s2) {
	bool ok = true;
	arrValores arr1, arr2;
	if (dame_num_celdas_libre(s1) != dame_num_celdas_libre(s2)) {
		ok = false;
	}
	for (int i = 0; i < MAX_VALORES; i++) {
		numero_posibles_valores(s1, arr1);
		numero_posibles_valores(s2, arr2);
		if (arr1[i] != arr2[2]) {
			ok = false;
		}
	}
	return ok;
}

bool operator<(tSudoku& s1, tSudoku& s2) {


}