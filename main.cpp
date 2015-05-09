#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "buscaminas.h"
using namespace std;

int main(){
   int filas, columnas, minas;
   srand(time(NULL));
   do{
		cout << "Dime el tamaño del tablero (filas y columnas, máximo 20x20): ";
		cin >> filas >> columnas;
		cout << "Dime el número de minas (no puede ser mayor que la mitad de las casillas): ";
		cin >> minas;
   }while (filas*columnas < 2*minas);
    CampoMinas mapa(filas, columnas, minas);

    mapa.PrettyPrint();
//    mapa.RevelarTablero();
   char accion;
   int fil, col;
   while(mapa.Ganado() == false && mapa.Explosionado() == false){
     do{
		cout << "Dime acción y posición (filas y columnas): \n";
		cout << "Ejemplo: a 0 1 (abrir fila 0, columna 1). m 5 5 (poner/quitar bandera fila 5, columna 5). \t";
		cin >> accion >> fil >> col;
     }while( (accion != 'a' && accion != 'm' && accion != 'A' && accion != 'M') 
			  || fil >= filas ||  col >= columnas || fil < 0 || col < 0	);

	  if (accion == 'a' || accion == 'A')
		mapa.PulsarBoton(fil, col);
	  else
		mapa.Marcar(fil,col);

       mapa.PrettyPrint();
   }

	mapa.RevelarTablero();
	if (mapa.Ganado())
		cout << "¡¡Has ganado!! ( ͡ᵔ ͜ʖ ͡ᵔ )\n";
	else
		cout << "¡¡Has perdido!! ¯\\_(ツ)_/¯\n";
cout << endl;
}
