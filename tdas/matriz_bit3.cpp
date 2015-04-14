#include <iostream>
#include <string>
#include <fstream>
#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////matriz_bit.cpp
bool Inicializar (MatrizBit& m, int fils, int cols){
  bool inicializar = true;
  unsigned int dim=0, aux=0;
  if( (fils * cols > 100 ) )
    inicializar = false;
    
    if (inicializar){
      for (int i=0; i<fils; i++){
        for (int j=0; j<cols; j++){
        m.matriz[i*cols + j] = 0;
        }
      }
    }
  dim = (dim | cols); // Operador OR a nivel de bit.
  aux = (fils << 16);
  dim += aux;
  m.dimension = dim;
    
  return inicializar;
}
int Filas (const MatrizBit& m){
  int fil = (m.dimension >> 16);
  return fil;
}
int Columnas (const MatrizBit& m){
  int col = ((m.dimension << 16) >> 16);
  return col;
}

bool Get(const MatrizBit& m,int f,int c){
  char caracter;
  bool casilla;
  if ( (f< Filas(m)) && (c<Columnas(m)) )
    caracter= m.matriz[f*Columnas(m) + c];
  else
    return 0;
  if (caracter == 1)
    casilla = true;
  else
    casilla = false;
    
  return casilla;
}

void Set(MatrizBit& m, int f,int c,bool v){
  if ( (f < Filas(m)) && (c < Columnas(m)) )
    m.matriz[f*Columnas(m) + c] = v;
}
