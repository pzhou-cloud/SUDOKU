#include "ListaSudokus.h"

void inicializaListaSudokus(tListaSudokus& ls) {
	ls.cont = 0;
	ls.capacidad = MAX_LISTA;
	ls.sudokus = new tSudoku * [ls.capacidad];

}
void destruyeListaSudokus(tListaSudokus& ls) {
	for (int i = 0; i < ls.cont; i++) {
		destruye(ls[i]);
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
					av[num - 1]++;
				}
			}


		}
	}
}

bool operator==(tSudoku& s1, tSudoku& s2) {

	bool mismaDificultad = true;
	arrValores av1, av2;

	if (dame_num_celdas_libre(s1) != dame_num_celdas_libre(s2)) {
		mismaDificultad = false;
	}else{

		numero_posibles_valores(s1, av1);
		numero_posibles_valores(s2, av2);
		
		int i = 0;

		while(i < MAX_VALORES && mismaDificultad){

			if(av1[i] != av2[i]){
				mismaDificultad = false;
			}
		}
	}

	return mismaDificultad;
}

bool operator<(tSudoku& s1, tSudoku& s2) {

	bool menorDificultad = true;

	int num_libres_s1 = dame_num_celdas_libre(s1);
	int num_libres_s2 = dame_num_celdas_libre(s2);

	if(num_libres_s1 < num_libres_s2){

		menorDificultad = true;

	}else if(num_libres_s1 == num_libres_s2){

		arrValores av1, av2;
		numero_posibles_valores(s1, av1);
		numero_posibles_valores(s2, av2);

		int i = 0;
		bool ok = true;

		while(i < MAX_VALORES - 1 && av1[i] == av2[i]){
			i++;
		}

		if(av1[i] > av2[i]){
			menorDificultad = true;
		}
	}

	return menorDificultad;
}

void insertar(tListaSudokus& ls, tSudoku& s){

	if(ls.cont == ls.capacidad){
		redimensionar(ls, ls.capacidad * 2);
	}

	int pos = 0;

	while(pos < ls.cont && *ls.sudokus[pos] < s){
		pos++;
	}

	for(int i = ls.cont; i > pos; i--){
		ls.sudokus[i] = ls.sudokus[i-1];
	}

	ls.sudokus[pos] = new tSudoku();
	inicializaSudokuCopia(*ls.sudokus[pos], s);
	ls.cont++;
}

void eliminar(tListaSudokus& ls, int pos){
	
	if(pos >= 0 && pos < ls.cont){
		
		destruye(*ls.sudokus[pos]);
		delete ls.sudokus[pos];

		for(int i = pos; i < ls.cont - 1; i++){
			ls.sudokus[i] = ls.sudokus[i + 1];
		}

		ls.cont--;
	}

}