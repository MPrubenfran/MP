#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
#include <iostream>
#include <string>
#include <fstream>
using namespace std
/////////////////////////////////////////////////////////////////////////////////////////////////matriz_bit.cpp
bool Inicializar (MatrizBit& m, int fils, int cols){
  bool inicializar = true;
  unsigned short int dim=0, aux=0;
  if( (fils * cols > 100 )
    inicializar = false;
  if (inicializar){
    for (int i=0; i<fils i++){
      for (int j=0; j<cols; j++){
        Set(m,fils, cols, 0);
      }
    }
  }
  aux = fils;
  aux = (aux << 8); //Desplazo filas y hago el | (OR) con las columnas al final.
  dim = cols;
  dim = ( dim | aux );

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
  if ( (f< Filas(m)) && (c<Columnas(m) )
    caracter= m.matriz[f*Columnas(m) + c];
  else
    return 0;
  if (caracter == 1)
    casilla = true;
  else
    casilla = false;
  return casilla;
}

void Set(MatrizBit& m, int f,int c,bool v){ ////// CUIDADO
  unsigned int aux = 1;
  int numero = f*Columnas(m) +c, numero_aux;
  int vector=0;
  if ( (f < Filas(m)) && (c < Columnas(m) ){
    while(numero >= 32){ //Nos dirá la posición en la que insertar el booleano dentro de unsigned int matriz[4]
      numero -= 32;
      vector++;
    } //matriz[vector] en el bit "numero"
    
    numero_aux = 31-numero;
    aux = ~ (aux << numero_aux); // 111...101....111;
    m.matriz[vector] = (m.matriz[vector] & aux);
    // a b c ... [v] ... y z
    // 1 1 1 ...  0  ... 1 1 &
    // a b c ...  0  ... y z -->
    if (v)
      aux = 1;
    else
      aux = 0;
    aux = (aux << numero_aux); // 000.1.000 o 000.0.000
    m.matriz[vector] = (m.matriz[vector] | aux);
    // a b c ... 0 ... y z
    // 0 0 0 ... v ... 0 0 |
    // a b c ... v ... y z
  }
}

/////////////////////////////////////Resto de funcinoes
bool Leer(std::istream& is, MatrizBit& m){
  bool exito = true;
  int filas, columnas;
  char caracter;
  if (is.fail())
    exito = false;
  else{
    if (is.peek() < 101){ // 1
    is >> filas;
    if (is.peek() < 101){
    is >> columnas;
    // Lectura1(); //true: éxito
    //////////////////////////////////////
    if (! is.fail() && filas*columnas < 101){
    Inicializar(m, filas, columnas),
    for (int i=0; i< filas; i++){
      for (int j=0; j< columnas; j++){
          is >> caracter;
        if (caracter == 1)
          m.matriz[i*columnas + j] = true;
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
bool Escribir(std::ostream& os,const MatrizBit& m){
bool exito = true;
os << m.filas << " " << m.columnas << endl;
for (int i=0; i< Filas(m); i++){
for (int j=0; j< Columnas(m); j++){
if (m.matriz[i*Columnas(m) + j] == 1)
  os << "1 ";
else
  os << "0 ";
}
os << endl;
}
  return exito;
}
bool Leer(const char nombre[],MatrizBit& m){
  ifstream is(nombre);
  bool exito = Leer(is, m);
  return exito;
}
bool Escribir(const char nombre[], const MatrizBit& m){
  ofstream os(nombre);
  bool exito= Escribir(os, m);
  return exito;
}
void Traspuesta(MatrizBit& res,const MatrizBit& m){
  unsigned int dim = ((m.dimension >> 16) << 16);
  dim += ((m.dimension << 16) >> 16);
  res.dimension = dim;
  for (int i=0; i< Filas(m); i++){
    for (int j=0; j< Columnas(m); j++)
      res.matriz[j*Filas(m) + i] = m.matriz[i*Columnas(m) + j];
  }
}
void And(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2){
  if ( (Filas(m1) == Filas(m2)) && (Columnas(m1) == Columnas(m2)) ){
    res.dimension = m1.dimension;
    for (int i=0; i< Filas(res)*Columnas(res); i++){
      if ( (m1.matriz[i] == false) || (m2.matriz[i] == false) ) // 0 false; 1 true;
        res.matriz[i] = false;
      else
        res.matriz[i] = true;
    }
  }
}
void Or(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2){
  if ( (Filas(m1) == Filas(m2)) && (Columnas(m1) == Columnas(m2)) ){
  res.dimension = m1.dimension;
    for (int i=0; i< Filas(res)*Columnas(res); i++){
      if ( (m1.matriz[i] == true) || (m2.matriz[i] == true) ) // 0 false; 1 true;
        res.matriz[i] = true;
      else
      res.matriz[i] = false;
    }
  }
}
void Not(MatrizBit& res,const MatrizBit& m){
  if ( (Filas(m1) == Filas(m2)) && (Columnas(m1) == Columnas(m2)) ){
    res.dimension = m1.dimension;
      for (int i=0; i< Filas(res)*Columnas(res); i++){
        res.matriz[i] = ! m.matriz[i];
      }
  }
}
