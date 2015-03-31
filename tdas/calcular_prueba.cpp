#include <iostream>
#include <fstream>
//#include 
using namespace std;

int main(int argc, char* argv[]){
  if (argc == 1) { // Si no hemos dado parámetros leemos los dos ficheros por la entrada estándar.
  }
  else if (argc == 2){
    ifstream f(argv[1]); // Como parámetro, el nombre del archivo, tenemos que leer el 2 por la entrada estándar.
    if (!f) {
      cerr << "Error: no se abre " << argv[1] << endl;
      return 1;
    }
  }
  else if (argc == 3){ // Abrimos primer fichero, creamos objeto, abrimos segundo fichero, creamos otro objeto, operaciones.
    ifstream f(argv[1]);
    if (!f) {
      cerr << "Error: no se abre " << argv[1] << endl;
      return 1;
    }
  }

cout << endl;
}
