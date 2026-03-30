#include "inputOutput.h"
#include <iomanip>
#include<iostream>

const int BARRA_HORIZONTAL = 196;
const int CRUZ = 197;
const int BARRA_VERTICAL = 179;
const int SEPARADOR_IZQUIERDO = 195;
const int ANCHO_CELDA = 3;
const int BLANCO = 250;

void pinta_numeros_columna(const tSudoku& s, int size) {
    cout << "   ";
    for (int c = 1; c <= dame_dimension(s); c++) {
        cout << " " << c << " ";
        if (c % size == 0) cout << " ";
    }
    cout << endl;
}

void pinta_fila_submatriz(int fila, int col, int size, const tSudoku& s) {
    
    for (int n = 0;  n < size; n++) {
        cout << " ";
       
        tCelda celda = dame_celda(s, fila, col);
        int v = dame_valor(celda);
        if (v == 0)  cout << char(BLANCO);
        else { 
            if (es_original(celda)) cout << ORANGE;
            cout << v << RESET; }
        cout << " ";
        col++;
    }
}

void pinta_separador_horizontal(const tSudoku& s, int size) {  // sobre el sudoku ??????
    cout <<  "  " << char(CRUZ);
    for (int i = 0; i < size; i++) {
        int hasta = ANCHO_CELDA * size;
        for (int i = 0; i < hasta; i++) cout << char(BARRA_HORIZONTAL);
        cout << char(CRUZ);
    }
    cout << endl;
}

void pinta_fila_matriz(int fila, const tSudoku& s) {
    int size = sqrt(dame_dimension(s));
    cout << fila + 1 << " ";
    cout << char(BARRA_VERTICAL);
    int col = 0;
    for (int ns = 0; ns < size; ns++) {
        pinta_fila_submatriz(fila, col, size, s);
        col = col + size;
        cout <<  char(BARRA_VERTICAL);
    }
    
    cout << endl;
}

void mostrar_juego_consola(const tSudoku& s) {
    int size = sqrt(dame_dimension(s));
    cout << endl;
    pinta_numeros_columna(s,size);
    pinta_separador_horizontal(s, size);

    for (int f = 0; f < dame_dimension(s) ;f++) {
        pinta_fila_matriz(f, s);
        if ((f+1) % size==0) pinta_separador_horizontal(s,3);
    }
    cout << endl;
}
 

// He cambiado Sudoku por tSudoku, Celda por tCelda y añadido el include <iostream> 
// del archivo que ha enviado la profe
