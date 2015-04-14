#include <iostream>
#include <string>
#include <fstream>
#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
using namespace std;


bool Inicializar (MatrizBit& m, int fils, int cols){
  bool inicializar = true;
  if (fils * cols > 128)
    inicializar = false;
  if (inicializar){
    for (int i=0; i<4; i++){
      matriz[i]=0;
    }
    m.dimension = (fils << 8) + cols;
  }
  return inicializar;
}

int Filas (const MatrizBit& m){
  int fils = (m.dimension >> 8);
  return fils;
}

int Columnas (const MatrizBit& m){
  int cols = m.dimension & 255;
  return cols;
}

bool Get(const MatrizBit& m, int f, int c){
  char caracter;
  bool casilla;
  int pos, e, d;
  if ((f < Filas(m)) && (c < Columnas(m)){
    pos = f*Columnas(m) + c;
    e = pos / 32;
    d = pos % 32;
    casilla = (m.matriz[e] >> d) & 1; // En todo caso sería [>> (31 -d)].
  }
  return casilla;
}

void Set(MatrizBit& m, int f,int c,bool v){
  unsigned int aux;
  int pos, e, d;
  
  if ( (f < Filas(m)) && (c < Columnas(m) ){
    pos = f*Columnas(m) + c;
    e = pos / 32;
    d = pos % 32;
    aux = 1 << d;
    
    matriz[e] = matriz[e] | aux;
    aux *= v;
    
    matriz[e] = matriz[e] & aux;
  }
}
