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

bool Leer(std::istream& is, MatrizBit& m){
  bool exito = true;
  if (is.fail())
      exito = false;
  else{
      if ( (is.peek() != 'X') && (is.peek() != '.')){ // 1
        int filas, columnas;
        bool aux;
        
        is >> filas;
        is >> columnas;
        
        if (Inicializar(m, filas, columnas)){
              for (int i=0; i< filas; i++){
                for (int j=0; j< columnas; j++){
                  is >> aux;
                  Set(m, i, j, aux);
                }
              }
        }
        else{ 
              cout << "No se ha podido leer la matriz." << endl;
              exito = false; 
        }
      }
      else if (is.peek() == 'X' || is.peek() == '.'){ // 2
        int i=0, j=0, k=0, columnas;
        char caracter;
        bool buffer[128];
        while ((is.peek() == 'X' || is.peek() == '.') && (k < 128)){
          j=0; 
            while(is.peek() != '\n'){
              is >> caracter;
              if (caracter == 'X')
                buffer[k] = true;
              else
                buffer[k] = false;
              
              j++;
              k++;
            }
            
          if (i == 0){
            columnas = j;
          }
          else{
            if (columnas != j)
               exito = false;
          }
          i++;
          while ( (is.peek() == '\n') || (is.peek() == '\t') || (is.peek() == ' ') )
            is.get(caracter); // Controlamos la entrada de datos saltando línea
        }
        
        if (k = 128){
          exito = false;
        }
        else{
          if (Inicializar(m, i, columnas){
          for (int l=0; l< Filas(m); l++ ){
              for (int p=0; p< Columnas(m); p++){
                Set(m, l, p, buffer[l*Columnas(m) + p]);
              }
            }
          }
          else
            exito = false;
        }
      }
      else  // 3
       exito = false;
     
      
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
  int filas, columnas;
  bool aux;
  
  filas = Filas(m);
  columnas = Columnas(m);
  
  Inicializar(res, columnas, filas);
  for (int i=0; i< filas; i++){
    for (int j=0; j< columnas; j++){
      aux = Get(m, i, j);
      Set(res, j, i, aux);
    }
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
        aux = Get(m1, i, j) && Get(m2, i, j);
        Set(res, i, j, aux);
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
        aux = Get(m1, i, j) || Get(m2, i, j);
        Set(res, i, j, aux);
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
      Set(res, i, j, aux);
    }
  }
}
