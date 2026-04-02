#include <iostream>
#include<fstream>
#include "Sudoku.h"
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
			switch (n) {
			case 1:{
				cout << "Fila y columna entre 1...9: ";
				cin >> f >> c;
				cout << "Valor: ";
				cin >> value;
				tCelda celda = dame_celda(s, f, c);

				if (pon_valor(s, f, c, value)) {
					cout << "correcto" << endl; // hay algo mal en el subprograma
				}
				else {
					cout << "no";
				}
				break;
			}

			case 2:{
				cout << "Fila y columna entre 1...9: ";
				cin >> f >> c;
				if (quita_valor(s, f, c)) {
					cout << "Correcto ";

				}
				else
					cout << "no";
				break;
			}

			case 3:{
				cout << "Fila y columna entre 1...9: ";
				cin >> f >> c;
				if (quita_valor(s, f, c)) {
					cout << "correcto";
				}
				else{
					cout << "no";
				}

			break;
			}

			case 4: {
				cout << "Fila y columna entre 1...9: ";
				cin >> f >> c;
				cout << "Los valores posibles para la celda son: { "; 
				int v = 1; 
				while (v <= 9) {
					if (es_valor_posible(s, f, c, v)) {
						cout << v << " "; 
					}
					v++;
				}
				cout << " }"; 
				break;
			}

			}
		}
	

		
	}
	

	return 0;
}


