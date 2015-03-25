
#include <iostream>
using namespace std;

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
  if (is.fail())
    fallo = true;
  if (! fallo){
    if (is.peek() <= 10){
      is >> m.filas;
      if (is.peek() <= 10)
        is >> m.columnas;
        for (int i=0; i< m.filas; i++){
          for (int j=0; j< m.columnas; j++)
            is >> m.matriz[i][j];
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
