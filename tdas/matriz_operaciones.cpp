#include "matriz_operaciones.h"
#include <iostream>
#include <string>
#include <fstream>

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
