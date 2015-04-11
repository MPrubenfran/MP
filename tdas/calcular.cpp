#include <iostream>
#include <fstream>
#include <string.h>
#include "matriz_bit.h"
#include "matriz_operaciones.h"
using namespace std;

int main(int argc, char* argv[]){
  if (argc == 1) { 
     cout << "Necesita especificar un tipo de operación.\n";
  }
/////////////////////////////
  else if (argc == 2){ // Si no hemos dado parámetros leemos los dos ficheros por la entrada estándar.
    MatrizBit ejemplo1, ejemplo2, resultado;
    
    if (strcmp(argv[1], "NOT") == 0){
      Leer(cin, ejemplo1);
      Not(resultado, ejemplo1);
      Escribir(cout, resultado);
    }
    else if (strcmp(argv[1], "TRS") == 0){
      Leer(cin, ejemplo1);
      Traspuesta(resultado, ejemplo1);
      Escribir(cout, resultado);
    }
    else if (strcmp(argv[1], "AND") == 0){
      Leer(cin, ejemplo1);
      Leer(cin, ejemplo2);
      And(resultado, ejemplo1, ejemplo2);
      Escribir(cout, resultado);
    }
    else if (strcmp(argv[1], "OR") == 0){
      Leer(cin, ejemplo1);
      Leer(cin, ejemplo2);
      Or(resultado, ejemplo1, ejemplo2);
      Escribir(cout, resultado);
    }
    else{
      cout << "Operación inválida"
    }
  }
//////////////////////////// Primera matriz se lee desde fichero y la otra por la entrada estándar.
  else if (argc == 3){ 
    ifstream f(argv[2]);
    MatrizBit ejemplo1, ejemplo2, resultado;
    if (!f) {
      cerr << "Error: no se abre " << argv[1] << endl;
      return 1;
    }
    else{
      if (strcmp(argv[1], "NOT") == 0){
        Leer(f, ejemplo1);
        Not(resultado, ejemplo1);
        Escribir(cout, resultado);
      }
      else if (strcmp(argv[1], "TRS") == 0){
        Leer(f, ejemplo1);
        Traspuesta(resultado, ejemplo1);
        Escribir(cout, resultado);
      }
      else if (strcmp(argv[1], "AND") == 0){
        Leer(f, ejemplo1);
        Leer(cin, ejemplo2);
        And(resultado, ejemplo1, ejemplo2);
        Escribir(cout, resultado);
      }
      else if (strcmp(argv[1], "OR") == 0){
        Leer(f, ejemplo1);
        Leer(cin, ejemplo2);
        Or(resultado, ejemplo1, ejemplo2);
        Escribir(cout, resultado);
      }
      else{
        cout << "Operación inválida"
      }
    }
  }
///////////////////////////// Ambas matrices se leen desde fichero.
  else if (argc == 4){
    ifstream f(argv[2]); // Como parámetro, el nombre del primer archivo.
    ifstream g(argv[3]); // Como parámetro, el nombre del segundo archivo.
    MatrizBit ejemplo1, ejemplo2, resultado;
    if (!f || !g) {
      if (!f)
        cerr << "Error: no se abre " << argv[2] << endl;
      if (!g)
        cerr << "Error: no se abre " << argv[3] << endl;
      return 1;
    }
    else{
      if (strcmp(argv[1], "NOT") == 0){
        cerr << "Operación unaria \"NOT\" no permitida.\n";
        return 1;
      }
      else if (strcmp(argv[1], "TRS") == 0){
        cerr << "Operación unaria \"TRS\" no permitida.\n";
        return 1;
      }
      else if (strcmp(argv[1], "AND") == 0){
        Leer(f, ejemplo1);
        Leer(g, ejemplo2);
        And(resultado, ejemplo1, ejemplo2);
        Escribir(cout, resultado);
      }
      else if (strcmp(argv[1], "OR") == 0){
        Leer(f, ejemplo1);
        Leer(g, ejemplo2);
        Or(resultado, ejemplo1, ejemplo2);
        Escribir(cout, resultado);
      }
      else{
        cout << "Operación inválida"
      }
    }
  }

cout << endl;
}
