#include <iostream>
#include <string>
#include <fstream>
#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
#include "matriz_operaciones.cpp"
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////////////matriz_bit.cpp


bool Inicializar (MatrizBit& m, int fils, int cols){
  bool inicializar = true;
  m.filas = fils;
  m.columnas = cols;
  if (fils * cols > 100)
    inicializar = false;
  if (inicializar){
    for (int i=0; i<fils*cols; i++)
        m.matriz[i] = 0;
  }
  return inicializar; 
}

int Filas (const MatrizBit& m){
  return m.filas;
}
int Columnas (const MatrizBit& m){
  return m.columnas;
}
bool Get(const MatrizBit& m,int f,int c){
  if ( (f<m.filas) && (c<m.columnas) )
    return m.matriz[f*m.columnas + c];
  else
    return 0;
}
void Set(MatrizBit& m, int f,int c,bool v){
  if ( (f < m.filas) && (c < m.columnas) )
      m.matriz[f*m.columnas + c] = v;
}
