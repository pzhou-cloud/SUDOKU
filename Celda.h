#pragma once
enum tEstado { ORIGINAL, OCUPADA, VACIA };

struct tCelda {
	int valor;
	tEstado estado;
};
using namespace std;

void inicializaCelda(tCelda& c);
void inicializaCelda(tCelda& c, int v, tEstado estado);

bool es_vacia(const tCelda& c);
bool es_original(const tCelda& c);
bool es_ocupada(const tCelda& c);

int dame_valor(const tCelda& c);
void pon_valor(tCelda& c, int v);
void pon_vacia(tCelda& c);
void pon_original(tCelda& c);
void pon_ocupada(tCelda& c);
