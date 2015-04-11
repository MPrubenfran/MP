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
    columnas = Columnas(m1)
    Inicializar(res, filas, columnas);
    
    for (int i=0; i < filas; i++){
      for (int j=0; j< columnas; j++){
        if ( (m1.matriz[i][j] == false) || (m2.matriz[i][j] == false) ) // 0 false; 1 true;
          res.matriz[i][j] = false;
        else
          res.matriz[i][j] = true;
      }
    }
  }
}
void Or(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2){
  if ( (m1.filas == m2.filas) && (m1.columnas == m2.columnas) ){
    res.filas = m1.filas;
    res.columnas = m1.columnas;
    for (int i=0; i< res.filas; i++){
      for (int j=0; j< res.columnas; j++){
        if ( (m1.matriz[i][j] == true) || (m2.matriz[i][j] == true) ) // 0 false; 1 true;
          res.matriz[i][j] = true;
        else
          res.matriz[i][j] = false;
      }
    }
  }
  
}
void Not(MatrizBit& res,const MatrizBit& m){
  if ( (m1.filas == m2.filas) && (m1.columnas == m2.columnas) ){
    res.filas = m1.filas;
    res.columnas = m1.columnas;
    for (int i=0; i< res.filas; i++){
      for (int j=0; j< res.columnas; j++)
        res.matriz[i][j] = ! m.matriz[i][j];
    }
  }
}
