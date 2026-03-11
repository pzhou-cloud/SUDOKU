#include <iostream>
#include<fstream>
#include "Sudoku.h"

using namespace std;

int main() {
	ifstream archivo;
	tSudoku s;
	archivo.open("sudoku_1.txt");
	if (archivo.is_open()) {
		carga_sudoku(archivo, s);
	}




	return 0;
}