#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
#include <iostream>
using namespace std

bool PuedeLeerFilas(){
  bool puede = false;
  if (cin.peek() < 11)
    puede= true;
  return puede;  
}

bool PuedeLeerColumnas(){
  bool puede = false;
  if (cin.peek() < 11)
    puede= true;
  return puede;  
}

bool Lectura(){
  bool exito_lectura;
  
  if (cin.fail()) 
    exito_lectura = false;
    
  if (exito_lectura){
    for (int i=0; i< m.filas; i++){
      for (int j=0; j< m.columnas; j++)
      is >> m.matriz[i][j];
    }
  }
  
  
  return exito_lectura;
}



bool Leer(const char nombre[],MatrizBit& m);
bool Escribir(const char nombre[], const MatrizBit& m);
void Traspuesta(MatrizBit& res,const MatrizBit& m);
void And(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2);
void Or(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2);
void Not(MatrizBit& res,const MatrizBit& m);
