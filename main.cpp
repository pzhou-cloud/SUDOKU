#include <iostream>
#include <fstream>
#include "ListaSudokus.h"
#include "inputOutput.h"

//Nota para Peipei: Yo estoy en Linux y al parecer lo de
//memoryleaks usa cosas exclusivas para windows y no funciona.

//Descomenta el include y lo del CrtSet de abajo cuando lo vayas a usar 
// ok

#include "memoryleaks.h"


using namespace std;

void mostrar_menu();
int pedir_opcion_valida();
void mostrar_casillas_bloqueadas(const tSudoku& s);

void cargar_lista_partidas(tListaSudokus& lp);
void cargar_partida(ifstream& archivo, tSudoku& s);

void cargar_lista_sudokus(tListaSudokus& ls);

void cargar_sudoku(ifstream& nombre_fichero_leido, tSudoku& sudoku);

char solicita_tipo_partida();


int elige_sudoku(tListaSudokus& ls);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ifstream archivo;
	tListaSudokus ls, lp;
	tSudoku s;
	int n;
	int f, c;
	int value;
	string nombre_fichero = "sudoku_2.txt";
	archivo.open(nombre_fichero);
	if (archivo.is_open())
	{
		inicializaSudoku(s);
		carga_sudoku(archivo, s);
		inicializaListaSudokus(ls);
		inicializaListaSudokus(lp);
		cargar_lista_sudokus(ls);
		cargar_lista_partidas(lp);


		int opcion;
		do
		{
			mostrar_juego_consola(s);
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
					cout << "Añadido correctamente" << endl;
					if (bloqueo(s)) {
						cout << "Sudoku bloqueado.....";
						cout << "Las casillas bloqueadas son: ";
						mostrar_casillas_bloqueadas(s);
						cout << endl;
					}
				}
				else
				{
					cout << "No puedes poner un " << value << " en (" << f << " , " << c << " )";
				}
			}

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
					cout << "No puedes quitar el valor en (" << f << " , " << c << " )" << endl;

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

				if (posibles_valores(s, f - 1, c - 1) != 0) {
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
					cout << " }" << endl;
				}
				else if (es_vacia(dame_celda(s, f - 1, c - 1))) {
					cout << "Nono, esa celda ya está ocupada" << endl;
				}
				else {
					cout << "Vaya, no hay ningún valor posible ahí" << endl;
				}


			}
			break;
			case 5:
			{
				autocompleta(s);

			}
			break;

			case 6:

				break;
			}
		} while (!terminado(s) && opcion != 6);

		if (terminado(s)) {
			cout << "Muy bien! te has pasado el juego";
		}
		else {
			cout << "Has salido del juego" << endl;
		}
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
	} while (opcion < 1 || opcion > 6);

	return opcion;
}

void mostrar_casillas_bloqueadas(const tSudoku& s) {

	int n = dame_num_celda_bloqueadas(s);
	int f, c;
	for (int i = 0; i < n; i++) {

		dame_celda_bloqueada(s, i, f, c);
		cout << "(" << f + 1 << "," << c + 1 << ")";
	}
}

void cargar_lista_partidas(tListaSudokus& lp) {
	ifstream archivo;
	bool ok = true;
	archivo.open("listaPartidas.txt");
	int np;
	if (!archivo.is_open()) {
		ok = false;
	}
	else {
		archivo >> np;
		int i = 0;
		while (i < np) {
			tSudoku* s = new tSudoku;
			inicializaSudoku(*s);
			cargar_partida(archivo, *s);
			insertar(lp, *s);
			i++;
		}
	}
}
void cargar_partida(ifstream& archivo, tSudoku& s) {

	carga_sudoku(archivo, s);
}



void cargar_lista_sudokus(tListaSudokus& ls) {
	ifstream archivo;
	bool ok = true;
	int ns;
	archivo.open("listaSudokus.txt");
	if (!archivo.is_open()) {
		ok = false;
	}
	else {
		archivo >> ns;
		int i = 0;
		while (i < ns) {
			tSudoku* s = new tSudoku;
			cargar_sudoku(archivo, *s);
			insertar(ls, *s);
			i++;
		}

	}

}

void cargar_sudoku(ifstream& nombre_fichero_leido, tSudoku& sudoku) {
	carga_sudoku(nombre_fichero_leido, sudoku);
}


char solicita_tipo_partida() {
	char opcion;
	tListaSudokus ls;
	cout << "Partida nueva (N), continuar partida (C) o abandonar la aplicacion (A)? ";
	cin >> opcion;
	opcion = toupper(opcion);
	switch (opcion) {
	case 'N': {
		elige_sudoku(ls);
		break;
	}
	case 'C': {
		elige_sudoku(ls);
		break;
	}
	case 'A':
	{
		cout << "Saliendo del juego... " << endl;
		break;
	}
	default:
		cout << "Opción no valida" << endl;

	}


	return opcion;

}
int elige_sudoku(tListaSudokus& ls) {
	mostrar_lista(ls);
	int opcion;
	cout << "Elige un sudoku: " << endl;
	cin >> opcion;

	return opcion;
}
