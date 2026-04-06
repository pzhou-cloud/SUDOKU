#include "Sudoku.h"

//Métodos privados de la versión 2:
void add_casillas_afectadas(tSudoku& s, int fila, int columna, int v);
void marca_valor_imposible(tSudoku& s, int f, int c, int v);
void quita_un_valor_imposible(tSudoku& s, int f, int c, int v);
void insertar_valor(tSudoku& s, int f, int c, int v);
void eliminar_valor(tSudoku& s, int f, int c, int v);
void remove_casillas_afectadas(tSudoku& s, int fila, int columna, int v);

//Métodos privados de la versión 1:
int posibles_valores(const tSudoku& s, int f, int c);
void inserta_celda_bloqueada(tSudoku& s, const tPosicion& pos);
void elimina_celda_bloqueada(tSudoku& s, const tPosicion& pos);
int num_celdas_originales(const tSudoku& s);
bool esta_en_zona_relevante(int f, int f_temp, int c, int c_temp);



void inicializaSudoku(tSudoku& s)
{	
	inicializaTablero(s.tablero, DIM);
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
	archivo >> s.tablero.dimension;

	for (int i = 0; i < dame_dimension(s); i++)
	{
		for (int j = 0; j < dame_dimension(s); j++)
		{

			archivo >> value;

			if (value == 0)
			{
				inicializaCelda(s.tablero.matriz[i][j]);
			}
			else
			{
				inicializaCelda(s.tablero.matriz[i][j], value, ORIGINAL);
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

bool nombre_temporal(const tSudoku& s, int f, int c, int v)
{
	return es_vacia(dame_celda(s,f,c)) && (v >= 1 && v <= 9);
}

bool esta_valor_en_fila(const tSudoku& s, int f, int v)
{

	bool ok = false;
	int c = 0;

	while (ok == false && c < DIM)
	{
		if (dame_valor(dame_celda(s, f, c))== v)
		{
			ok = true;
		}
		c++;
	}

	return ok;
}

bool esta_valor_en_columna(const tSudoku& s, int c, int v)
{

	bool ok = false;
	int f = 0;

	while (ok == false && f < DIM)
	{
		
		if (dame_valor(dame_celda(s, f, c)) == v)
		{
			ok = true;
		}
		f++;
	}

	return ok;
}

bool esta_valor_en_bloque(const tSudoku& s, int f, int c, int v)
{

	bool ok = false;
	int f_esquina_bloque = f / 3 * 3;
	int c_esquina_bloque = c / 3 * 3;
	int i = f_esquina_bloque;
	int j = c_esquina_bloque;

	while (!ok && i < f_esquina_bloque + 3)
	{

		j = c_esquina_bloque;

		while (!ok && j < c_esquina_bloque + 3)
		{
			if (dame_valor(dame_celda(s, i, j)) == v)
			{
				ok = true;
			}
			j++;
		}
		i++;
	}

	return ok;
}

bool es_valor_posible(const tSudoku& s, int f, int c, int v)
{

	return s.valores_celda.valores[f][c][v-1].posible && es_vacia(dame_celda(s, f, c));
}

void actualiza_celdas_bloqueadas(tSudoku& s)
{

	s.celdas_bloqueadas.cont = 0;

	for (int f = 0; f < DIM; f++)
	{
		for (int c = 0; c < DIM; c++)
		{
			if (posibles_valores(s, f, c) == 0)
			{
				s.celdas_bloqueadas.bloqueadas[s.celdas_bloqueadas.cont].fila = f;
				s.celdas_bloqueadas.bloqueadas[s.celdas_bloqueadas.cont].columna = c;
				s.celdas_bloqueadas.cont++;
			}
		}
	}
}

bool pon_valor(tSudoku& s, int f, int c, int v)
{

	bool ok = false;

	if (es_valor_posible(s, f, c, v) && f >= 0 && f < DIM && c >= 0 && c < DIM && v >= 1 && v <= 9)
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
	if (f >= 0 && f < DIM && c >= 0 && c < DIM && !es_vacia(dame_celda(s, f, c)) && !es_original(dame_celda(s, f, c)))
	{

		eliminar_valor(s, f, c, dame_celda(s, f, c).valor);
		ok = true;
	}
	return ok;
}



int num_celdas_originales(const tSudoku& s){
	int suma = 0;
	for(int i = 0; i < DIM; i++){
		for(int j = 0; j < DIM; j++){
			if(es_original(dame_celda(s, i, j))){
				suma++;
			}
		}
	}

	return suma;
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

	
	s.cont_numeros = num_celdas_originales(s);
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

	for(int j = 0; j < DIM; j++){

		if(j != c){
			quita_un_valor_imposible(s, f, j, v);

		}

	}

	for(int i = 0; i < DIM; i++){

		if(i != f){
			quita_un_valor_imposible(s, i, c, v);

		}
	}

	int fila_esquina_submatriz = f / 3 * 3;
	int columna_esquina_submatriz = c / 3 * 3;

	for(int i = fila_esquina_submatriz; i < fila_esquina_submatriz + 3; i++){
		for(int j = columna_esquina_submatriz; j < columna_esquina_submatriz + 3; j++){

			if(i != f && j != c){
				quita_un_valor_imposible(s, i, j, v);

			}

		}
	}

}

void insertar_valor(tSudoku& s, int f, int c, int v){

	pon_valor(s.tablero.matriz[f][c], v);
	pon_ocupada(s.tablero.matriz[f][c]);
	s.cont_numeros++;
	add_casillas_afectadas(s, f, c, v);

}

void eliminar_valor(tSudoku& s, int f, int c, int v){

	pon_vacia(s.tablero.matriz[f][c]);
	pon_valor(s.tablero.matriz[f][c], 0);
	s.cont_numeros--;
	remove_casillas_afectadas(s, f, c, v);
}