#include "Sudoku.h"

//Métodos privados versión 2:
void add_casillas_afectadas(tSudoku& s, int fila, int columna, int v);
void marca_valor_imposible(tSudoku& s, int f, int c, int v);
void quita_un_valor_imposible(tSudoku& s, int f, int c, int v);
void insertar_valor(tSudoku& s, int f, int c, int v);
void eliminar_valor(tSudoku& s, int f, int c, int v);
void remove_casillas_afectadas(tSudoku& s, int fila, int columna, int v);

//Métodos privados versión 1:
int posibles_valores(const tSudoku& s, int f, int c);
void inserta_celda_bloqueada(tSudoku& s, const tPosicion& pos);
void elimina_celda_bloqueada(tSudoku& s, const tPosicion& pos);
bool esta_en_zona_relevante(int f, int f_temp, int c, int c_temp);
bool posicion_dentro_de_limites(int f, int c);
bool valor_valido(int v);



void inicializaSudoku(tSudoku& s)
{	
	inicializaTablero(s.tablero);
	s.cont_numeros = 0;
	s.celdas_bloqueadas.cont = 0;
	s.valores_celda.nFilas = DIM;
	s.valores_celda.nColumnas = DIM;

	for(int f = 0; f < DIM; f++){
		for(int c = 0; c < DIM; c++){
			for(int v = 0; v < MAX_VALORES; v++){

				s.valores_celda.valores[f][c][v].posible = true;
				s.valores_celda.valores[f][c][v].celdas_que_afectan = 0;

			}
		}
	}
}

void carga_sudoku(ifstream& archivo, tSudoku& s)
{

	int value;
	int tablero_dimension;
	archivo >> tablero_dimension;

	for (int i = 0; i < tablero_dimension; i++)
	{
		for (int j = 0; j < tablero_dimension; j++)
		{

			archivo >> value;

			if (value == 0)
			{	
				tCelda celda;
				inicializaCelda(celda);
				pon_elemento(s.tablero, i, j, celda);
			}
			else
			{	
				tCelda celda;
				inicializaCelda(celda, value, ORIGINAL);
				pon_elemento(s.tablero, i, j, celda);
				s.cont_numeros++;
				add_casillas_afectadas(s, i, j, value);
			}
		}
	}
}

int dame_dimension(const tSudoku& s)
{
	return dame_dimension(s.tablero);
}

tCelda dame_celda(const tSudoku& s, int f, int c)
{
	return dame_elem(s.tablero, f,c) ;
}

bool terminado(const tSudoku& s)
{
	return s.cont_numeros == dame_dimension(s) * dame_dimension(s);
}

bool bloqueo(const tSudoku& s)
{
	return s.celdas_bloqueadas.cont != 0;
}

int dame_num_celda_bloqueadas(const tSudoku& s)
{
	return s.celdas_bloqueadas.cont;
}

void dame_celda_bloqueada(const tSudoku& s, int p, int& f, int& c)
{
	f = s.celdas_bloqueadas.bloqueadas[p].fila;
	c = s.celdas_bloqueadas.bloqueadas[p].columna;
}


bool es_valor_posible(const tSudoku& s, int f, int c, int v)
{

	return s.valores_celda.valores[f][c][v-1].posible && es_vacia(dame_celda(s, f, c));
}


bool pon_valor(tSudoku& s, int f, int c, int v)
{

	bool ok = false;

	if (es_valor_posible(s, f, c, v) && posicion_dentro_de_limites(f, c) && v >= 1 && v <= 9)
	{

		insertar_valor(s, f, c, v);

		ok = true;
	}

	return ok;
}

bool esta_en_zona_relevante(int f, int f_temp, int c, int c_temp){
	return (f == f_temp) || (c == c_temp) || (f_temp / 3 == f / 3 && c_temp / 3 == c / 3);
}


bool quita_valor(tSudoku& s, int f, int c)
{
	bool ok = false;
	if (posicion_dentro_de_limites(f, c) && !es_vacia(dame_celda(s, f, c)) && !es_original(dame_celda(s, f, c)))
	{

		eliminar_valor(s, f, c, dame_celda(s, f, c).valor);
		ok = true;
	}
	return ok;
}

void reset(tSudoku& s)
{

	for (int i = 0; i < DIM; i++)
	{
		for (int j = 0; j < DIM; j++)
		{
			quita_valor(s, i, j);		

		}
	}

	s.celdas_bloqueadas.cont = 0;
}

void autocompleta(tSudoku& s)
{
	int v = 1;
	bool hay_cambios;

	do
	{
		hay_cambios = false;
		for (int f = 0; f < DIM; f++)
		{
			for (int c = 0; c < DIM; c++)
			{
				if (es_vacia(dame_celda(s, f, c)) && posibles_valores(s, f, c) == 1)
				{
					v = 1;
					while (v <= 9 && !pon_valor(s, f, c, v))
					{
						v++;
					}
					hay_cambios = true;

				}

			}
		}

	} while (hay_cambios);
}

int posibles_valores(const tSudoku& s, int f, int c)
{
	int v = 1;
	int num = 0;

	if (es_vacia(dame_celda(s, f, c)))
	{
		while (v <= MAX_VALORES)
		{
			if (s.valores_celda.valores[f][c][v-1].posible)
			{
				num++;
			}
			v++;
		}
	}

	return num;
}

void inserta_celda_bloqueada(tSudoku& s, const tPosicion& pos){
	
	s.celdas_bloqueadas.bloqueadas[s.celdas_bloqueadas.cont] = pos;
	s.celdas_bloqueadas.cont++;
}

void elimina_celda_bloqueada(tSudoku& s, const tPosicion& pos){

	bool encontrada = false;
	int p = 0;

	while(p < s.celdas_bloqueadas.cont && !encontrada){

		if(s.celdas_bloqueadas.bloqueadas[p].fila == pos.fila &&
		s.celdas_bloqueadas.bloqueadas[p].columna == pos.columna)
		{

			encontrada = true;
			for(int i = p; i < s.celdas_bloqueadas.cont - 1; i++){
				s.celdas_bloqueadas.bloqueadas[i] = s.celdas_bloqueadas.bloqueadas[i + 1];
			}

			s.celdas_bloqueadas.cont--;

		}else{
			p++;
		}
	}
}

void marca_valor_imposible(tSudoku& s, int f, int c, int v){

	bool esta_ya_bloqueada = false;

	if(posibles_valores(s, f, c) == 0){
		esta_ya_bloqueada = true;
	}

	s.valores_celda.valores[f][c][v-1].posible = false;
	s.valores_celda.valores[f][c][v-1].celdas_que_afectan++;

	if(!esta_ya_bloqueada && posibles_valores(s, f, c) == 0 && es_vacia(dame_celda(s, f, c))){

		tPosicion posicion_bloqueada;
		posicion_bloqueada.fila = f;
		posicion_bloqueada.columna = c;
		inserta_celda_bloqueada(s, posicion_bloqueada);
	}
}

void quita_un_valor_imposible(tSudoku& s, int f, int c, int v){

	bool esta_ya_bloqueada = false;

	if(posibles_valores(s, f, c) == 0){
		esta_ya_bloqueada = true;
	}

	s.valores_celda.valores[f][c][v-1].celdas_que_afectan--;

	if(s.valores_celda.valores[f][c][v-1].celdas_que_afectan == 0){
		s.valores_celda.valores[f][c][v-1].posible = true;
	}

	if(esta_ya_bloqueada && posibles_valores(s, f, c) > 0 && es_vacia(dame_celda(s, f, c))){
		tPosicion posicion_desbloqueada;
		posicion_desbloqueada.fila = f;
		posicion_desbloqueada.columna = c;
		elimina_celda_bloqueada(s, posicion_desbloqueada);
	}
}

void add_casillas_afectadas(tSudoku& s, int f, int c, int v){

	for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {

            if ((i != f || j != c) && esta_en_zona_relevante(f, i, c, j)) {
                marca_valor_imposible(s, i, j, v);
            }
        }
    }

}

void remove_casillas_afectadas(tSudoku& s, int f, int c, int v){

	for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {

            if ((i != f || j != c) && esta_en_zona_relevante(f, i, c, j)) {
                quita_un_valor_imposible(s, i, j, v);
            }
        }
    }
}

void insertar_valor(tSudoku& s, int f, int c, int v){

	tCelda celda = dame_celda(s, f, c);
	pon_valor(celda, v);
	pon_ocupada(celda);
	pon_elemento(s.tablero, f, c, celda);
	s.cont_numeros++;
	add_casillas_afectadas(s, f, c, v);

}

void eliminar_valor(tSudoku& s, int f, int c, int v){

	tCelda celda = dame_celda(s, f, c);
	pon_vacia(celda);
	pon_valor(celda, 0);
	pon_elemento(s.tablero, f, c, celda);
	s.cont_numeros--;
	remove_casillas_afectadas(s, f, c, v);
}

bool posicion_dentro_de_limites(int f, int c){
	return f >= 0 && f < DIM && c >= 0 && c < DIM;
}

bool valor_dentro_de_limites(int v){
	return v >= 1 && v <= MAX_VALORES;
}