#include <iostream>
#include <string>
#include <fstream>
#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
#include "matriz_operaciones.cpp"
using namespace std


/////////////////////////////////////////////////////////////////////////////////////////////////matriz_bit.cpp


bool Inicializar (MatrizBit& m, int fils, int cols){
  bool inicializar = true;
  if (fils * cols > 100)
    inicializar = false;
  if (inicializar){
    for (int i=0; i<fils*cols; i++)
        m.matriz[i] = 0;
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
    return m.matriz[f*m.columnas + c];
  else
    return 0;
}
void Set(MatrizBit& m, int f,int c,bool v){
  if ( (f < m.filas) && (c < m.columnas) )
      m.matriz[f*m.columnas + c] = v;
}


/////////////////////////////////////Resto de funcinoes
bool Leer(std::istream& is, MatrizBit& m){
  bool exito = true;
  int filas= m.filas, columnas= m.columnas;
  char booleano;
  if (is.fail())
      exito = false;
  else{
      if (is.peek() < 101){ // 1
        is >> m.filas;
        if (is.peek() < 101){
         is >> m.columnas;
    //     Lectura1(); //true: éxito
            if ( m.filas * m.columnas < 101 ){
              for (int i=0; i< m.filas*m.columnas; i++){
                is >> m.matriz[i*m.columnas + j];
              }
            }
            else
              exito = false;
        }
        else
          exito= false;
      }
      else if (is.peek() == 'X' || is.peek() == '.'){ // 2
        int i=0, j;
        char caracter;
        m.columnas =0;
        
        while ( (is.peek() == 'X' || is.peek() == '.') && exito ){
          j=0;
            while(is.peek() != '\n' && is.peek() != '\t'){
              is >> caracter;
              if (caracter == 'X')
                m.matriz[i*m.columnas +j] = true;
              else
                m.matriz[i*m.columnas +j] = false;
              
              j++;
            }
            
          if (i == 0){
            if (j < 101)
              m.columnas=j;
            else
              exito = false;
          }
          i++;
            
            while ( (is.peek() == '\n') || (is.peek() == '\t') || (is.peek() == ' ') )
              is.get(caracter); // Controlamos la entrada de datos saltando línea
          
        }
        m.filas =i;
        if (m.filas * m.columnas > 100)
          exito = false;
      }
        //Lectura2(); //true: éxito
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
