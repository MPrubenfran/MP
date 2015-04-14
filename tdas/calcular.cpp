#include <iostream>
#include <fstream>
#include <string.h>
#include "matriz_bit.h"
#include "matriz_operaciones.h"
using namespace std;


bool  DimensionesIguales(const MatrizBit& m1, const MatrizBit& m2){
    bool exito = false;
    if ( (Filas(m1) == Filas(m2)) && (Columnas(m1) == Columnas(m2)) )
        exito = true;
    return exito;
}

int main(int argc, char* argv[]){
    MatrizBit ejemplo1, ejemplo2, resultado;
    bool booleano = true;
  if (argc == 1) { 
     cout << "Necesita especificar un tipo de operación.\n";
  }
/////////////////////////////
  else if (argc == 2){ // Si no hemos dado parámetros leemos los dos ficheros por la entrada estándar.
    if (strcmp(argv[1], "NOT") == 0){
      if ( Leer(cin, ejemplo1) )
        Not(resultado, ejemplo1);
      else{
        booleano = false;  
        cout << "No se ha podido leer.\n";
      }
    }
    else if (strcmp(argv[1], "TRS") == 0){
      if ( Leer(cin, ejemplo1) )
        Traspuesta(resultado, ejemplo1);
      else{
        booleano = false;
        cout << "No se ha podido leer.\n";
      }  
    }
    else if (strcmp(argv[1], "AND") == 0){
      if ( Leer(cin, ejemplo1) && Leer(cin, ejemplo2) ){
        if ( DimensionesIguales(ejemplo1, ejemplo2) )
            And(resultado, ejemplo1, ejemplo2);
        else{
            booleano = false;
            cout << "Dimensiones de las matrices diferentes.\n";
        }
      }
      else{
        booleano = false;
        cout << "No se ha podido leer.\n";
      }
    }
    else if (strcmp(argv[1], "OR") == 0){
      if ( Leer(cin, ejemplo1) && Leer(cin, ejemplo2) ){
        if ( DimensionesIguales(ejemplo1, ejemplo2) )
           Or(resultado, ejemplo1, ejemplo2);
        else{
            booleano = false;
            cout << "Dimensiones de las matrices diferentes.\n";
        }
      }
      else{
        booleano = false;
        cout << "No se ha podido leer.\n";
      }
    }
    else{
      cout << "Operación inválida.\n";
      booleano = false;
    }
    
    if (booleano)
      Escribir(cout, resultado);
  }
//////////////////////////// Primera matriz se lee desde fichero y la otra por la entrada estándar.
  else if (argc == 3){ 
    ifstream f(argv[2]);
    if (!f) {
      cerr << "Error: no se abre " << argv[2] << "." << endl;
      return 1;
    }
    else{
      if (strcmp(argv[1], "NOT") == 0){
        if ( Leer(f, ejemplo1) )
          Not(resultado, ejemplo1);
        else{
          booleano = false;
          cout << "No se ha podido leer.\n";
        }
      }
      else if (strcmp(argv[1], "TRS") == 0){
        if ( Leer(f, ejemplo1) )
          Traspuesta(resultado, ejemplo1);
        else{
          booleano = false;        
          cout << "No se ha podido leer.\n";
        }
      }
      else if (strcmp(argv[1], "AND") == 0){
        if (Leer(f, ejemplo1) && Leer(cin, ejemplo2)){
            if ( DimensionesIguales(ejemplo1, ejemplo2) )
                And(resultado, ejemplo1, ejemplo2);
            else{
                booleano = false;
                cout << "Dimensiones de las matrices diferentes.\n";
            }
        }
        else{
          booleano = false;
          cout << "No se ha podido leer.\n";
        }
      }
      else if (strcmp(argv[1], "OR") == 0){
        if ( Leer(f, ejemplo1) && Leer(cin, ejemplo2) ){
            if ( DimensionesIguales(ejemplo1, ejemplo2) )
                Or(resultado, ejemplo1, ejemplo2);
            else{
                booleano = false;
                cout << "Dimensiones de las matrices diferentes.\n";
            }
        }
        else{
            booleano = false;        
            cout << "No se ha podido leer.\n";
        }
      }
      else{
        cout << "Operación inválida";
        booleano = false;
      }
      
      if (booleano)
        Escribir(cout, resultado);
    }
  }
///////////////////////////// Ambas matrices se leen desde fichero.
  else if (argc == 4){
    ifstream f(argv[2]); // Como parámetro, el nombre del primer archivo.
    ifstream g(argv[3]); // Como parámetro, el nombre del segundo archivo.
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
        if ( Leer(f, ejemplo1) && Leer(g, ejemplo2) ){
            if ( DimensionesIguales(ejemplo1, ejemplo2) )
                And(resultado, ejemplo1, ejemplo2);
            else{
                booleano = false;
                cout << "Dimensiones de las matrices diferentes.\n";
            }
        }
        else{
          booleano = false;
          cout << "No se ha podido leer.\n";
        }
      }
      else if (strcmp(argv[1], "OR") == 0){
        if ( Leer(f, ejemplo1) && Leer(g, ejemplo2) ){
            if ( DimensionesIguales(ejemplo1, ejemplo2) )
                Or(resultado, ejemplo1, ejemplo2);
            else{
                booleano = false;
                cout << "Dimensiones de las matrices diferentes.\n";
            }
        }
        else{
          booleano = false;        
          cout << "No se ha podido leer.\n";
        }
      }
      else{
        cout << "Operación inválida.\n";
        booleano = false;
      }
      
      if (booleano)
        Escribir (cout, resultado);
    }
  }

cout << endl;
}
