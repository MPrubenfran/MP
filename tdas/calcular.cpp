#include <iostream>
#include <fstream>
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
    
    if( (argv[1] == "NOT") ||(argv[1] == "Not") || (argv[1] == "not") ){
      Leer(cin, ejemplo1);
      Not(resultado, ejemplo1);
      Escribir(cout, resultado);
    }
    else if( (argv[1] == "TRS") ||(argv[1] == "Trs") || (argv[1] == "trs")  ){
      Leer(cin, ejemplo1);
      Traspuesta(resultado, ejemplo1);
      Escribir(cout, resultado);
    }
    else if ( (argv[1] == "AND") ||(argv[1] == "And") || (argv[1] == "and")  ){
      Leer(cin, ejemplo1);
      Leer(cin, ejemplo2);
      And(resultado, ejemplo1, ejemplo2);
      Escribir(cout, resultado);
    }
    else if ( (argv[1] == "OR") ||(argv[1] == "Or") || (argv[1] == "or")  ){
      Leer(cin, ejemplo1);
      Leer(cin, ejemplo2);
      Or(resultado, ejemplo1, ejemplo2);
      Escribir(cout, resultado);
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
      if( (argv[1] == "NOT") ||(argv[1] == "Not") || (argv[1] == "not") ){
        Leer(f, ejemplo1);
        Not(resultado, ejemplo1);
        Escribir(cout, resultado);
      }
      else if( (argv[1] == "TRS") ||(argv[1] == "Trs") || (argv[1] == "trs")  ){
        Leer(f, ejemplo1);
        Traspuesta(resultado, ejemplo1);
        Escribir(cout, resultado);
      }
      else if ( (argv[1] == "AND") ||(argv[1] == "And") || (argv[1] == "and")  ){
        Leer(f, ejemplo1);
        Leer(cin, ejemplo2);
        And(resultado, ejemplo1, ejemplo2);
        Escribir(cout, resultado);
      }
      else if ( (argv[1] == "OR") ||(argv[1] == "Or") || (argv[1] == "or")  ){
        Leer(f, ejemplo1);
        Leer(cin, ejemplo2);
        Or(resultado, ejemplo1, ejemplo2);
        Escribir(cout, resultado);
      }
  }
///////////////////////////// Ambas matrices se leen desde fichero.
  else if (arg == 4){
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
      if( (argv[1] == "NOT") ||(argv[1] == "Not") || (argv[1] == "not") ){
        cerr << "Operación unaria \"NOT\" no permitida.\n";
        return 1;
      }
      else if( (argv[1] == "TRS") ||(argv[1] == "Trs") || (argv[1] == "trs")  ){
        cerr << "Operación unaria \"TRS\" no permitida.\n";
        return 1;
      }
      else if ( (argv[1] == "AND") ||(argv[1] == "And") || (argv[1] == "and")  ){
        Leer(f, ejemplo1);
        Leer(g, ejemplo2);
        And(resultado, ejemplo1, ejemplo2);
        Escribir(cout, resultado);
      }
      else if ( (argv[1] == "OR") ||(argv[1] == "Or") || (argv[1] == "or")  ){
        Leer(f, ejemplo1);
        Leer(g, ejemplo2);
        Or(resultado, ejemplo1, ejemplo2);
        Escribir(cout, resultado);
      }
    }
  }

cout << endl;
}
