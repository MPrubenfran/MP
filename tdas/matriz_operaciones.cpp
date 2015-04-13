#include <iostream>
#include <string>
#include <fstream>
#include "matriz_operaciones.h"
#include "matriz_bit.h"

bool Escribir(std::ostream& os,const MatrizBit& m){
  bool exito = true;
  os << Filas(m) << " " << Columnas(m) << endl;
  for (int i=0; i< Filas(m); i++){
    for (int j=0; j< Columnas(m); j++){
      os << Get(m, i, j) << " ";
    }
    os << endl;
  }
    return exito;
}

bool Escribir(const char nombre[], const MatrizBit& m){
  ofstream os(nombre);
  bool exito= Escribir(os, m);
  return exito;
}

void Traspuesta(MatrizBit& res,const MatrizBit& m){
  int filas, columnas;
  bool aux;
  
  filas = Filas(m);
  columnas = Columnas(m);
  
  Inicializar(res, columnas, filas);
  for (int i=0; i< filas; i++){
    for (int j=0; j< columnas; j++)
      aux = Get(m, filas, columnas);
      Set(res, columnas, filas, aux);
  }
}
void And(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2){
  int filas, columnas;
  bool aux;
  
  if ( (Filas(m1) == Filas(m2)) && (Columnas(m1) == Columnas(m2)) ){
    filas = Filas(m1);
    columnas = Columnas(m1);
    Inicializar(res, filas, columnas);
    
    for (int i=0; i < filas; i++){
      for (int j=0; j< columnas; j++){
        aux = Get(m1, filas, columnas) && Get(m2, filas, columnas);
        Set(res, filas, columnas, aux);
      }
    }
  }
}
void Or(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2){
  int filas, columnas;
  bool aux;
  
  if ( (Filas(m1) == Filas(m2)) && (Columnas(m1) == Columnas(m2)) ){
    filas = Filas(m1);
    columnas = Columnas(m1);
    Inicializar(res, filas, columnas);
    
    for (int i=0; i < filas; i++){
      for (int j=0; j< columnas; j++){
        aux = Get(m1, filas, columnas) || Get(m2, filas, columnas);
        Set(res, filas, columnas, aux);
      }
    }
  }
}
void Not(MatrizBit& res,const MatrizBit& m){
  int filas, columnas;
  bool aux;
  
  filas = Filas(m);
  columnas = Columnas(m);
  
  Inicializar(res, filas, columnas);
  
  for (int i=0; i < filas; i++){
    for (int j=0; j < columnas; j++){
      aux = !Get(m, i, j);
      Set(res, filas, columnas, aux);
    }
  }
}
