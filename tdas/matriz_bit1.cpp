#include <iostream>
#include <string>
#include <fstream>
#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////matriz_bit.cpp


bool Inicializar (MatrizBit& m, int fils, int cols){
  bool inicializar = true;
  m.filas = fils;
  m.columnas = cols;
  if( (fils > 10) || (cols > 10) )
    inicializar = false;
  if (inicializar){
    for (int i=0; i<10; i++){
      for (int j=0; j<10; j++){
        m.matriz[i][j] = 0;
      }
    }
  }
  
  return inicializar; 
}

int Filas (const MatrizBit& m){
  return m.filas;
}
int Columnas (const MatrizBit& m){
  return m.columnas;
}
bool Get(const MatrizBit& m, int f, int c){
  if ( (f<m.filas) && (c<m.columnas) )
    return m.matriz[f][c];
  else
    return 0;
}
void Set(MatrizBit& m, int f, int c, bool v){
  if ( (f < m.filas) && (c < m.columnas) )
      m.matriz[f][c] = v;
}
