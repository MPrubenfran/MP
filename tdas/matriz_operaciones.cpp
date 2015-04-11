#include "matriz_operaciones.h"
#include <iostream>
#include <string>
#include <fstream>

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
  
  filas = Filas(m);
  columnas = Columnas(m);
  
  Inicializar(res, filas, columnas);
  
  for (int i=0; i < filas; i++){
    for (int j=0; j < columnas; j++){
      aux = !Get(m, filas, columnas);
      Set(res, filas, columnas, aux);
    }
  }
}
