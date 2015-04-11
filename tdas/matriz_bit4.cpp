#include <iostream>
#include <string>
#include <fstream>
#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
#include "matriz_operaciones.cpp"
using namespace std


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
  int cols = (m.dimension << 8) >> 8;
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
    casilla = (m.matriz[e] >> d) & 1;
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

/////////////////////////////////////Resto de funcinoes
bool Leer(std::istream& is, MatrizBit& m){
  bool exito = true;
  int filas, columnas;
  bool caracter;
  if (is.fail())
    exito = false;
  else{
    if (is.peek() < 128){
      is >> filas;
      if ((is.peek() * filas) < 128){
        is >> columnas;
        if (! is.fail()){
          Inicializar(m, filas, columnas),
          for (int i=0; i< filas; i++){
            for (int j=0; j< columnas; j++){
              is >> caracter;
              Set(m, i, j, caracter);
            }
          }
        }
      }
    }
  }
    else
      exito=false;
    }
    else
      exito= false;
    }
    else if (is.peek() == 'X' || is.peek() == '.'){ // 2
      int i=0, j;
      filas = columnas = 0;
      unsigned int dim=0, aux=0;
      while (is.peek() == 'X' || is.peek() == '.'){
        j=0;
        while(is.peek() != '\n' && is.peek() != '\t'){
        is >> caracter;
        if (caracter == 'X')
          m.matriz[i*columnas + j] = true;
        else
          m.matriz[i*columnas + j] = false;
        j++;
        }
      if (i == 0)
        columnas = j;
      i++;
      while ( (is.peek() == '\n') || (is.peek() == '\t') || (is.peek() == ' ') )
        is.get(caracter); // Controlamos la entrada de datos saltando línea
      }
      filas =i;
      dim = (dim | columnas); // Operador OR a nivel de bit.
      aux = (filas << 16);
      dim += aux;
      m.dimension = dim;
    }
    else // 3
      exito = false;
  }
  return exito;
}

bool Leer(const char nombre[],MatrizBit& m){
  ifstream is(nombre);
  bool exito = Leer(is, m);
  return exito;
}
