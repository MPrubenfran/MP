#include <iostream>
#include <string>
#include <fstream>
#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////matriz_bit.cpp


bool Inicializar (MatrizBit& m, int fils, int cols){
  bool inicializar = true;
  m.filas = fils;
  m.columnas = cols;
  if( (fils > 10) || (cols > 10) )
    inicializar = false;
  if (inicializar){
    for (int i=0; i<10; i++){
      for (int j=0; j<10; j++){
        m.matriz[i][j] = 0;
      }
    }
  }
  
  return inicializar; 
}

int Filas (const MatrizBit& m){
  return m.filas;
}
int Columnas (const MatrizBit& m){
  return m.columnas;
}
bool Get(const MatrizBit& m,int f,int c){
  if ( (f<m.filas) && (c<m.columnas) )
    return m.matriz[f][c];
  else
    return 0;
}
void Set(MatrizBit& m, int f,int c,bool v){
  if ( (f < m.filas) && (c < m.columnas) )
      m.matriz[f][c] = v;
}


/////////////////////////////////////Resto de funcinoes
bool Leer(std::istream& is, MatrizBit& m){
  bool exito = true;
  if (is.fail())
      exito = false;
  else{
      if ( (is.peek() != 'X') && (is.peek() != '.')){ // 1
        is >> m.filas;
         is >> m.columnas;
          if (! is.fail() && m.filas < 11 && m.columnas < 11){
                for (int i=0; i< m.filas; i++){
                  for (int j=0; j< m.columnas; j++){
                    is >> m.matriz[i][j];
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
        while (is.peek() == 'X' || is.peek() == '.'){
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
        Inicializar(m, i, columnas);
        for (int l=0; l< Filas(m); l++ ){
          for (int p=0; p< Columnas(m); p++){
            Set(m, l, p, buffer[l*Columnas(m) + p]);
          }
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
