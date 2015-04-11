#include <iostream>
#include <string>
#include <fstream>
#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
#include "matriz_operaciones.cpp"
using namespace std

/////////////////////////////////////////////////////////////////////////////////////////////////matriz_bit.cpp


bool Inicializar (MatrizBit& m, int fils, int cols){
  bool inicializar = true;
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
  int filas= m.filas, columnas= m.columnas;
  char booleano;
  if (is.fail())
      exito = false;
  else{
      if (is.peek() < 11){ // 1
        is >> m.filas;
        if (is.peek() < 11){
         is >> m.columnas;
    //     Lectura1(); //true: éxito
    //////////////////////////////////////
            if (! is.fail() ){
              for (int i=0; i< m.filas; i++){
                for (int j=0; j< m.columnas; j++)
                is >> m.matriz[i][j];
              }
            }
        }
        else
          exito= false;
      }
      else if (is.peek() == 'X' || is.peek() == '.'){ // 2
        int i=0, j;
        char caracter;
        
        while (is.peek() == 'X' || is.peek() == '.'){
          j=0;
            while(is.peek() != '\n' && is.peek() != '\t'){
              is >> caracter;
              if (caracter == 'X')
                m.matriz[i][j] = true;
              else
                m.matriz[i][j] = false;
              
              j++;
            }
            
          if (i == 0)
            m.columnas = j;
          i++;
            
            while ( (is.peek() == '\n') || (is.peek() == '\t') || (is.peek() == ' ') )
              is.get(caracter); // Controlamos la entrada de datos saltando línea
          
        }
        m.filas =i;
      }
        //Lectura2(); //true: éxito
      else  // 3
       exito = false;
     
      
  }
  return exito;
}



bool Escribir(std::ostream& os,const MatrizBit& m){
  bool exito = true;
  os << m.filas << " " << m.columnas << endl;
    for (int i=0; i< m.filas; i++){
      for (int j=0; j< m.columnas; j++)
        os << m.matriz[i][j];
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
