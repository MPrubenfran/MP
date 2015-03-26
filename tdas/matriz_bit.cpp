/**
  * @file matriz_bit.cpp
  * @brief Fichero de definiciones para insertar la implementación deseada
  *
  * Incluye la definición correspondiente dependiendo de la selección en matriz_bit.h
  * 
  * @warning Este fichero no se debe modificar
  *
  */

#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
#include <iostream>
using namespace std;

#if CUAL_COMPILO==1
  #include "matriz_bit1.cpp"
#elif CUAL_COMPILO==2
  #include "matriz_bit2.cpp"
#elif CUAL_COMPILO==3
  #include "matriz_bit3.cpp"
#else
  #include "matriz_bit4.cpp"
#endif


bool Inicializar (MatrizBit& m, int fils, int fils, int cols){
  for (int i=0; i<10; i++){
    for (int j=0; j<10; j++){
      m.matriz[i][j] = 0;
    }
  }
}
int Filas (const MatrizBit& m){
  return m.filas;
}
int Columnas (const MatrizBit& m){
  return m.columnas;
}
bool Get(const MatrizBit& m,int f,int c){
  return m.matriz[f][c];
}
void Set(MatrizBit& m,int f,int c,bool v){
  m.matriz[f][c] = v;
}

bool Leer(std::istream& is,MatrizBit& m){
  bool fallo = false;
  int filas= m.filas, columnas= m.columnas;
  char booleano;
  
  if (is.fail())
    fallo = true;
  if (! fallo){
      if (is.peek() <= 10){
        
        is >> m.filas;
        if (is.peek() <= 10){
          is >> m.columnas;
          for (int i=0; i< m.filas; i++){
            for (int j=0; j< m.columnas; j++)
              is >> m.matriz[i][j];
          }
        }
      } 
      
      else if ( is.peek() == 'X' || is.peek() == '.' ){
        int filas=0;
        bool parada = false;
          while (( is.peek() == 'X' || is.peek() == '.' ) && (! parada)){
            if (is.peek() == 'X'){
              m.matriz[][] = true;
              is >> booleano;
            }
            else if (ispeek() == '.')
              m.matriz[][] = false;
              is >> booleano;
            else 
              parada = true;
          }
      }  
        
  }
  if (is.fail())
    fallo = true;
    
  return fallo;
  
}
bool Escribir(std::ostream& os,const MatrizBit& m){
  bool fallo = false;
  int filas= m.filas, columnas= m.columnas;
    for (int i=0; i< filas; i++){
      for (int j=0; j< columnas; j++)
        os << m.matriz[i][j];
    }
    
  return fallo;
}
bool Leer(const char nombre[],MatrizBit& m);
bool Escribir(const char nombre[], const MatrizBit& m);
void Traspuesta(MatrizBit& res,const MatrizBit& m);
void And(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2);
void Or(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2);
void Not(MatrizBit& res,const MatrizBit& m);
