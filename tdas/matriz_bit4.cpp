#include <iostream>
#include <string>
#include <fstream>
#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
#include "matriz_operaciones.cpp"
using namespace std


bool Inicializar (MatrizBit& m, int fils, int cols){
  bool inicializar = true;
  if (fils * cols > 128)
    inicializar = false;
  if (inicializar){
    for (int i=0; i<4; i++){
      matriz[i]=0;
    }
    m.dimension = (fils << 8) + cols;
  }
  return inicializar;
}

int Filas (const MatrizBit& m){
  int fils = (m.dimension >> 8);
  return fils;
}

int Columnas (const MatrizBit& m){
  int cols = (m.dimension << 8) >> 8;
  return cols;
}

bool Get(const MatrizBit& m, int f, int c){
  char caracter;
  bool casilla;
  int pos, e, d;
  if ((f < Filas(m)) && (c < Columnas(m)){
    pos = f*Columnas(m) + c;
    e = pos / 32;
    d = pos % 32;
    casilla = (m.matriz[e] >> d) & 1;
  }
  return casilla;
}

void Set(MatrizBit& m, int f,int c,bool v){
  unsigned int aux;
  int pos, e, d;
  
  if ( (f < Filas(m)) && (c < Columnas(m) ){
    pos = f*Columnas(m) + c;
    e = pos / 32;
    d = pos % 32;
    aux = 1 << d;
    
    matriz[e] = matriz[e] | aux;
    aux *= v;
    
    matriz[e] = matriz[e] & aux;
  }
}
void Set2(MatrizBit& m, int pos,bool v){
    int e, d;
    e = pos / 32;
    d = pos % 32;
    aux = 1 << d;
    
    matriz[e] = matriz[e] | aux;
    aux *= v;
    
    matriz[e] = matriz[e] & aux;
  }
}

/////////////////////////////////////Resto de funcinoes
bool Leer(std::istream& is, MatrizBit& m){
  int filas, columnas;
  bool aux;
  bool exito = true;
  
  if (is.fail())
      exito = false;
  else{
      if ( (is.peek() != 'X') && (is.peek() != '.')){ // 1
        is >> filas;
        is >> columnas;

        if (! is.fail() && (filas * columnas <= 128)){
          Inicializar(m, filas, columnas);
          for (int i=0; i<filas; i++){
            for (int j=0; j<columnas; j++)
            is >> aux;
            Set(m, i, j, aux);
          }
        }
        else{ 
              cout << "No se ha podido leer la matriz." << endl;
              exito = false; 
        }
      }
      else if (is.peek() == 'X' || is.peek() == '.'){ // 2
        int i=0, j;
        int p=0
        char caracter;
        
        while (is.peek() == 'X' || is.peek() == '.'){
          j=0;
            while(is.peek() != '\n'){
              is >> caracter;
              if (caracter == 'X')
                Set2(m, p, true);
              else
                Set2(m, p, false);
              p++;
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

bool Leer(const char nombre[],MatrizBit& m){
  ifstream is(nombre);
  bool exito = Leer(is, m);
  return exito;
}
