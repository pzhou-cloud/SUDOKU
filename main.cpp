#include <iostream>
#include <fstream>
#include "ListaSudokus.h"
#include "inputOutput.h"

// #include "memoryleaks.h"

using namespace std;

void mostrar_menu();
int pedir_opcion_valida();
void mostrar_casillas_bloqueadas(const tSudoku &s);

void cargar_lista_partidas(tListaSudokus &lp);
void cargar_partida(ifstream &archivo, tSudoku &s);

void cargar_lista_sudokus(tListaSudokus &ls);

void cargar_sudoku(ifstream &nombre_fichero_leido, tSudoku &sudoku);

char solicita_tipo_partida();

int elige_sudoku(tListaSudokus &ls);

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ifstream archivo;
	tListaSudokus ls, lp;
	tSudoku s;
	int numSudoku;

	inicializaListaSudokus(ls);
	inicializaListaSudokus(lp);

	cargar_lista_sudokus(ls);
	cargar_lista_partidas(lp);

	char tipoPartida = solicita_tipo_partida();

	switch (tipoPartida)
	{
	case 'N':
		numSudoku = elige_sudoku(ls);
		copiaIndependiente(s, ls[numSudoku - 1]);

		int subOpcion = preguntar_ver_o_jugar();

		if (subOpcion == 1)
		{
			mostrar_juego_consola(s);
		}
		else
		{
			bool abandonado = jugar(s);
			if (abandonado)
			{
				insertar(lp, s);
				cout << "Partida guardada en la lista de partidas." << endl;
			}
		}
		break;

	case 'C':
		if (dame_num_elem(lp) > 0)
		{
			numSudoku = elige_sudoku(lp);
			copiaIndependiente(s, lp[numSudoku - 1]);

			int subOpcion = preguntar_ver_o_jugar();

			if (subOpcion == 1)
			{
				mostrar_juego_consola(s);
			}
			else
			{
				bool abandonado = jugar(s);
				eliminar(lp, numSudoku - 1);
				if (abandonado)
				{
					insertar(lp, s); // Se inserta el nuevo estado[cite: 3]
					cout << "Progreso actualizado en la lista de partidas." << endl;
				}
			}
		}
		else
		{
			cout << "No hay partidas previas. ¡Prueba una partida nueva!" << endl;
		}
		break;

	case 'A':
		cout << "Cerrando aplicación..." << endl;
		break;

	default:
		cout << "Opción no reconocida." << endl;
		break;
	}

	guardar_lista_partidas(lp);
	destruyeListaSudokus(ls);
	destruyeListaSudokus(lp);
	destruye(s);

	return 0;
}

void mostrar_menu()
{

	cout << "1.- poner numero " << endl;
	cout << "2.- quitar numero " << endl;
	cout << "3.- reset " << endl;
	cout << "4.- posibles valores de una celda vacía" << endl;
	cout << "5.- autocompletar celdas con valor unico " << endl;
	cout << "6.- resolver el sudoku" << endl;
	cout << "7.- salir" << endl;
}

int pedir_opcion_valida()
{
	int opcion;

	do
	{
		cout << "Elige una opcion: ";
		cin >> opcion;
	} while (opcion < 1 || opcion > 7);

	return opcion;
}

void mostrar_casillas_bloqueadas(const tSudoku &s)
{

	int n = dame_num_celda_bloqueadas(s);
	int f, c;
	for (int i = 0; i < n; i++)
	{

		dame_celda_bloqueada(s, i, f, c);
		cout << "(" << f + 1 << "," << c + 1 << ")";
	}
}

void cargar_lista_partidas(tListaSudokus &lp)
{
	ifstream archivo;
	archivo.open("listaPartidas.txt");
	int num_partidas;
	if (archivo.is_open())
	{
		archivo >> num_partidas;
		int i = 0;
		while (i < num_partidas)
		{
			tSudoku s;
			inicializaSudoku(s);
			cargar_partida(archivo, s);
			insertar(lp, s);
			destruye(s);
			i++;
		}
	}

	archivo.close();
}

void cargar_partida(ifstream &archivo, tSudoku &s)
{

	carga_sudoku(archivo, s);
	int f, c, v;
	archivo >> f;
	while (f != -1)
	{
		archivo >> c >> v;
		pon_valor(s, f - 1, c - 1, v);
		archivo >> f;
	}
}

void cargar_lista_sudokus(tListaSudokus &ls)
{
	ifstream archivo_general;
	ifstream archivo_tablero;
	int num_sudokus;
	string nombre_fichero;

	archivo_general.open("listaSudokus.txt");

	if (archivo_general.is_open())
	{
		archivo_general >> num_sudokus;

		for (int i = 0; i < num_sudokus; i++)
		{
			archivo_general >> nombre_fichero;

			archivo_tablero.open(nombre_fichero);

			if (archivo_tablero.is_open())
			{

				tSudoku s;
				inicializaSudoku(s);
				carga_sudoku(archivo_tablero, s);
				insertar(ls, s);
				destruye(s);

				archivo_tablero.close();
			}
		}

		archivo_general.close();
	}
}

void cargar_sudoku(ifstream &nombre_fichero_leido, tSudoku &sudoku)
{
	carga_sudoku(nombre_fichero_leido, sudoku);
}

char solicita_tipo_partida()
{
	char opcion;
	do
	{
		cout << "Partida nueva (N), continuar partida (C) o abandonar la aplicacion (A)? ";
		cin >> opcion;

		if (opcion != 'N' && opcion != 'C' && opcion != 'A')
		{
			cout << "La opción seleccionada (' " << opcion << " ') " << "no es válida" << endl;
		}
	} while (opcion != 'N' && opcion != 'C' && opcion != 'A');

	return opcion;
}

int elige_sudoku(tListaSudokus &ls)
{
	mostrar_lista(ls);
	int opcion;
	cout << "Elige un sudoku: " << endl;
	cin >> opcion;

	return opcion;
}

bool jugar(tSudoku &s)
{
	int f, c, value;
	int opcion;
	bool abandonado = false;

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
				if (bloqueo(s))
				{
					cout << "Sudoku bloqueado.....";
					cout << "Las casillas bloqueadas son: ";
					mostrar_casillas_bloqueadas(s);
					cout << endl;
				}
			}
			else
			{
				cout << "No puedes poner un " << value << " en (" << f << " , " << c << " )" << endl;
			}
		}
		break;

		case 2:
		{
			cout << "Fila y columna entre 1...9: ";
			cin >> f >> c;
			if (quita_valor(s, f - 1, c - 1))
			{
				cout << "Correcto " << endl;
			}
			else
			{
				cout << "No puedes quitar el valor en (" << f << " , " << c << " )" << endl;
			}
		}
		break;

		case 3:
			reset(s);
			break;

		case 4:
		{
			cout << "Fila y columna entre 1...9: ";
			cin >> f >> c;

			if (posibles_valores(s, f - 1, c - 1) != 0)
			{
				cout << "Los valores posibles para la celda son: { ";
				for (int v = 1; v <= 9; v++)
				{
					if (es_valor_posible(s, f - 1, c - 1, v))
					{
						cout << v << " ";
					}
				}
				cout << " }" << endl;
			}
			else if (!es_vacia(dame_celda(s, f - 1, c - 1)))
			{
				cout << "Nono, esa celda ya está ocupada" << endl;
			}
			else
			{
				cout << "Vaya, no hay ningún valor posible ahí" << endl;
			}
		}
		break;

		case 5:
			autocompleta_simple(s);
			break;

		case 6:
			autocompleta_total(s);
			break;
		case 7:
			abandonado = true;
			break;
		}
	} while (!terminado(s) && !abandonado);

	if (terminado(s))
	{
		cout << "¡Muy bien! Te has pasado el juego." << endl;
	}
	else
	{
		cout << "Has salido del juego." << endl;
	}

	return abandonado;
}

void guardar_partida(ofstream &archivo, const tSudoku &s)
{

	archivo << 9 << endl;
	for (int f = 0; f < 9; f++)
	{

		for (int c = 0; c < 9; c++)
		{

			tCelda celda = dame_celda(s, f, c);
			if (es_original(celda))
			{
				archivo << dame_valor(celda) << " ";
			}
			else
			{
				archivo << "0 ";
			}
		}
		archivo << endl;
	}

	for (int f = 0; f < 9; f++)
	{
		for (int c = 0; c < 9; c++)
		{
			tCelda celda = dame_celda(s, f, c);
			if (es_ocupada(celda))
			{
				archivo << f + 1 << " " << c + 1 << " " << dame_valor(celda) << endl;
			}
		}
	}

	archivo << "-1" << endl;
}

void guardar_lista_partidas(tListaSudokus &lp)
{
	ofstream archivo("listaPartidas.txt");
	if (archivo.is_open())
	{
		int n = dame_num_elem(lp);
		archivo << n << endl;

		for (int i = 0; i < n; i++)
		{

			guardar_partida(archivo, lp[i]);
		}
		archivo.close();
	}
	else
	{
		cout << "Error al abrir el archivo para guardar las partidas." << endl;
	}
}

int preguntar_ver_o_jugar()
{
	int subOpcion;
	cout << "\n1. Ver un sudoku" << endl;
	cout << "2. Jugar un sudoku" << endl;
	do
	{
		cout << "Elige opcion: ";
		cin >> subOpcion;
	} while (subOpcion != 1 && subOpcion != 2); // Validación simple
	return subOpcion;
}