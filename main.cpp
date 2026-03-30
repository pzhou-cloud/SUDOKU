#include <iostream>
#include<fstream>
#include "inputOutput.h"

using namespace std;

int main() {
	ifstream archivo;
	tSudoku s;
	int n;
	int f, c;
	int value; 
	archivo.open("sudoku_1.txt");
	if (archivo.is_open()) {
		carga_sudoku(archivo, s);
		mostrar_juego_consola(s);
		cout << "1.- poner numero " << endl;
		cout << "2.- quitar numero " << endl;
		cout << "3.- reset " << endl;
		cout << "4.- posibles valores de una celda vacía" << endl;
		cout << "5.- autocompletar celdas con valor unico " << endl;
		cout << "6.- salir" << endl;
		cout << "Elige una opcion: ";
		cin >> n;
		if (n >= 1 && n <= 6) {
			cout << "Fila y columna entre 1...9: ";
			cin >> f >> c;
			tCelda celda = dame_celda(s, f, c);
			cout << "Los valores posibles para la celda son: { " << dame_valor(celda) << " }" << endl; // cambiar el dame_valor

		}
		cout << "Valor: ";
		cin >> value;

		switch (n) {
		case 1:
			if (pon_valor(s, f, c, value)) {
				cout << "correcto" << endl;
			}
			else {
				cout << "no"; 
			}
			break;
		case 2: break;


		}
	}
	

	return 0;
}

