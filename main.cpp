#include <iostream>
#include <fstream>
#include "Sudoku.h"
#include "inputOutput.h"

using namespace std;

void mostrar_menu();
int pedir_opcion_valida();

int main()
{
	ifstream archivo;
	tSudoku s;
	int n;
	int f, c;
	int value;
	string nombre_fichero = "sudoku_1.txt";
	archivo.open(nombre_fichero);
	if (archivo.is_open())
	{

		inicializaSudoku(s);
		carga_sudoku(archivo, s);
		mostrar_juego_consola(s);
		int opcion;
		do
		{
			mostrar_menu();
			opcion = pedir_opcion_valida();

			switch (opcion)
			{
			case 1:
			{
				cout << "Fila y columna entre 1...9: ";

				cin >> f >> c;
				cout << "Valor: ";
				cin >> value;

				if (pon_valor(s, f - 1, c - 1, value))
				{
					cout << "correcto" << endl; // hay algo mal en el subprograma
				}
				else
				{
					cout << "No puedes poner un " << value << " en (" << f << " , " << c << " )";
				}
			}
				mostrar_juego_consola(s);
				break;
			case 2:
			{
				cout << "Fila y columna entre 1...9: ";
				cin >> f >> c;
				if (quita_valor(s, f - 1, c - 1))
				{
					cout << "Correcto ";
				}
				else
					cout << "No puedes quitar el valor en (" << f << " , " << c << " )";
			}
			break;
			case 3:
			{
				reset(s);
			}
			break;
			case 4:
			{
				cout << "Fila y columna entre 1...9: ";
				cin >> f >> c;
				cout << "Los valores posibles para la celda son: { ";
				int v = 1;
				while (v <= 9)
				{
					if (es_valor_posible(s, f - 1, c - 1, v))
					{
						cout << v << " ";
					}
					v++;
				}
				cout << " }";
			}
			break;
			case 5:
			{
				autocompleta(s);
			}
			break;

			case 6:
				// Nada, se sale del bucle
				break;
			}
		} while (!terminado(s) && opcion != 6);
	}
	else
	{
		cout << "Error al abrir " << nombre_fichero;
	}

	return 0;
}

void mostrar_menu()
{

	cout << "1.- poner numero " << endl;
	cout << "2.- quitar numero " << endl;
	cout << "3.- reset " << endl;
	cout << "4.- posibles valores de una celda vacía" << endl;
	cout << "5.- autocompletar celdas con valor unico " << endl;
	cout << "6.- salir" << endl;
}

int pedir_opcion_valida()
{
	int opcion;

	do
	{
		cout << "Elige una opcion: ";
		cin >> opcion;
	} while (opcion < 1 && opcion > 6);

	return opcion;
}