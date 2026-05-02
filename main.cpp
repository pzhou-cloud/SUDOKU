#include <iostream>
#include <fstream>
#include "ListaSudokus.h"
#include "inputOutput.h"

//Recordatorio para Peipei: Yo estoy en Linux y al parecer la wea esa
//de memoryleaks usa cosas exclusivas para windows entonces se me crashea
//descomenta el include y lo del CrtSet de abajo cuando lo vayas a usar

//#include "memoryleaks.h"


using namespace std;

void mostrar_menu();
int pedir_opcion_valida();
void mostrar_casillas_bloqueadas(const tSudoku& s);

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ifstream archivo;
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
					if(bloqueo(s)){
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

				if(posibles_valores(s, f - 1, c - 1) != 0){
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
				}else if(es_vacia(dame_celda(s, f - 1, c - 1))){
					cout << "Nono, esa celda ya está ocupada" << endl;
				}else{
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

		if(terminado(s)){
			cout << "Muy bien! te has pasado el juego";
		}else{
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

void mostrar_casillas_bloqueadas(const tSudoku& s){

	int n = dame_num_celda_bloqueadas(s);
	int f, c;
	for(int i = 0; i < n; i++){

		dame_celda_bloqueada(s, i, f, c);
		cout << "(" << f + 1 << "," << c + 1 << ")"; 
	}
}