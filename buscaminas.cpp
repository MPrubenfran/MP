#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <cassert>
#include <iomanip>
#include "buscaminas.h"
using namespace std;

#define RESET      "\x1b[0m"
#define ROJO       "\x1b[31m"
#define VERDE      "\x1b[32m"
#define AMARILLO   "\x1b[33m"
#define AZUL       "\x1b[34m"
#define BLANCO     "\x1b[37m"
#define NEGRO      "\x1b[30m"
#define NEGRITA_ON  "\x1b[1m"
#define INTERMITENTE  "\x1b[42m"


struct CeldaPosicion{
	int fila, columna;
	CeldaPosicion *sig;
};

void Liberar(CeldaPosicion*& pend){
	CeldaPosicion *aux=0;
	while(pend !=0){
		aux=pend;
		pend = pend ->sig;
		delete aux;
	}
}

void Tablero::Inicializar(int fil, int col){
  if (fil <= TAM && col <= TAM){
	filas = fil;
	columnas = col;
  }
  else
	filas = columnas = 0;
  for (int i=0; i<fil; i++){
	for (int j=0; j<col; j++)
	  Modificar(i, j, false, false, false);
  }
}

inline
int Tablero::Filas() const{
	return filas;
}
inline
int Tablero::Columnas() const{
	return columnas;
}

Casilla Tablero::Elemento(int fil, int col) const{
  assert(PosicionCorrecta(fil, col));
  return datos[fil][col];
}

void Tablero::Modificar(int fil, int col, bool bom, bool ab, bool marc){
  if (fil < filas && col < columnas && fil >= 0 && col >= 0){	
	datos[fil][col].abierta = ab;
	datos[fil][col].bomba = bom;
	datos[fil][col].marcada = marc;
  }
}

void Tablero::InsertarMinas(int min){
	int x,y;
	srand(time(NULL));
	while(min > 0){
		x = rand()%filas;
		y = rand()%columnas;		
		if (datos[x][y].bomba == false){
			datos[x][y].bomba = true;
			min--;
		}
	}
}

void Tablero::CambiarMarca(int f, int c){
	if (f<filas && c< columnas && f >= 0 && c >= 0)
		datos[f][c].marcada = !datos[f][c].marcada;
	else
		cerr << "Error en marcado.\n";
}

void Tablero::Abrir(int f, int c){
	assert(PosicionCorrecta(f, c));
		datos[f][c].abierta = true;
}

int CampoMinas::MinasProximas(int fil, int col) const{
	int minas=0;
	for (int i=fil-1; i <= fil+1; i++){
		for (int j=col-1; j <= col+1; j++){
			if (tab.PosicionCorrecta(i,j) && tab.Elemento(i,j).bomba)
				minas++;
		}
	}
	return minas;
}


CampoMinas::CampoMinas(int filas, int columnas, int min){
	tab.Inicializar(filas, columnas);
	tab.InsertarMinas(min);
}
inline
int CampoMinas::Filas() const{
	return tab.Filas();
}
inline
int CampoMinas::Columnas() const{
	return tab.Columnas();
}
bool CampoMinas::Explosionado() const{
	int f = tab.Filas(), c = tab.Columnas();
	bool exp = false;
	for (int i=0; i< f && !exp; i++){
		for (int j=0; j< c && !exp; j++){
			if (tab.Elemento(i,j).bomba == true && tab.Elemento(i,j).abierta == true )
				exp = true;
		}
	}
	return exp;
}

bool CampoMinas::Ganado() const{
	bool exito = false;
	if (Explosionado() == false){
		exito = true;
		for(int i=0; i< tab.Filas() && exito; i++){
			for (int j=0;j< tab.Columnas() && exito; j++){
				if (tab.Elemento(i,j).bomba == false && tab.Elemento(i,j).abierta == false )
					exito = false;					
			}
		}
	}
	return exito;
}

bool CampoMinas::Marcar(int fil, int col){
	bool exito = true;
	if (tab.Elemento(fil,col).abierta == false)
		tab.CambiarMarca(fil,col);
	else
		return false;
	return exito;
}

bool CampoMinas::Abrir(int fil, int col){
	bool exito = false;
	if (!tab.Elemento(fil,col).marcada && !tab.Elemento(fil,col).abierta){
		tab.Abrir(fil, col);
		exito = true;
	}
	return exito;
}

void CampoMinas::ImprimeCasilla(int n) const{
			if (n == 1)
				cout << AZUL << "①  " << RESET;
			else if (n == 2)
				cout << VERDE << "②  " << RESET;
			else if (n == 3)
				cout << ROJO << "③  " << RESET;
			else if (n == 4)
				cout << AZUL << NEGRITA_ON << "④  " << RESET;
			else if (n == 5)
				cout << ROJO << NEGRITA_ON << "⑤  " << RESET;
			else if (n == 6)
				cout << AMARILLO << "⑥  " << RESET;
			else if (n == 7)
				cout << NEGRO << "⑦  " << RESET;
			else if (n == 8)
				cout << AMARILLO << NEGRITA_ON << "⑧  " << RESET;
}

void CampoMinas::PrettyPrint() const{
	cout << " ";
	for (int i=0; i<tab.Columnas(); i++){
		cout << setw(3) << i;
		if (i == 9)
			cout << " ";
	}

	cout << endl;
	for (int i=0; i<tab.Filas(); i++){
		if (i<10)
			cout << i << "  ";
		else
			cout << i << " ";
		for (int j=0; j< tab.Columnas(); j++){
	        if (tab.Elemento(i,j).abierta == false && tab.Elemento(i,j).marcada == false)
				cout << "●  ";
			else if (MinasProximas(i,j) != 0 && tab.Elemento(i,j).abierta && !tab.Elemento(i,j).bomba)
				ImprimeCasilla(MinasProximas(i,j));
	        else if (tab.Elemento(i,j).abierta == false && tab.Elemento(i,j).marcada == true)
				cout << ROJO << "⚑  " << RESET;
	        else if (tab.Elemento(i,j).abierta && tab.Elemento(i,j).bomba)
				cout << AMARILLO << NEGRITA_ON  <<"💣  " << RESET;
			else
				cout << "○  ";
		}
		cout <<endl;
	}
	cout << endl;
}

void CampoMinas::RevelarTablero() const{
	cout << " ";
	for (int i=0; i<tab.Columnas(); i++){
		cout << setw(3) << i;
		if (i == 9)
			cout << " ";
	}
	cout << endl;
	for (int i=0; i<tab.Filas(); i++){
		if (i<10)
			cout << i << "  ";
		else
			cout << i << " ";
		for (int j=0; j< tab.Columnas(); j++){
	        if (tab.Elemento(i,j).bomba && !tab.Elemento(i,j).abierta)
				cout <<"💣  " << RESET;
			else if (tab.Elemento(i,j).bomba && tab.Elemento(i,j).abierta)
				cout << AMARILLO << NEGRITA_ON  <<"💣  " << RESET;
			else if (MinasProximas(i,j) != 0)
				ImprimeCasilla(MinasProximas(i,j));
			else
				cout << "○  ";
		}
		cout <<endl;
	}
	cout << endl;
}


bool Tablero::PosicionCorrecta(int f, int c) const{
	return (f>=0 && c>=0 && f< filas && c < columnas);
}
bool BuscarCelda (CeldaPosicion *&p, CeldaPosicion &celda){
	bool estar = false;
	CeldaPosicion *aux = p;

	while (aux != 0 && !estar){
		if ((aux -> fila == celda.fila) && (aux -> columna == celda.columna))
			estar = true;

		aux = aux->sig;
	}
	return estar;
}


void Extraer(CeldaPosicion *&pend){
   if (pend != 0){
		CeldaPosicion *apuntador = pend;
		pend = pend -> sig;
		delete apuntador;
   }
}

void Aniadir(CeldaPosicion *&pend, int f, int c){
	CeldaPosicion *aux = new CeldaPosicion;
	aux->sig = pend;
	aux->fila = f;
	aux->columna = c; 
	pend = aux;
}

void CampoMinas::PulsarBoton(int fil, int col){
	CeldaPosicion *pend =0, *aux =0, celda;
	bool hay_celdas = true;
   if (MinasProximas(fil, col) > 0 && !tab.Elemento(fil, col).marcada)
	 	tab.Abrir(fil,col);
   else if (!tab.Elemento(fil, col).marcada){
		aux = pend = new CeldaPosicion;
		pend->fila = fil; pend->columna = col; pend->sig = 0;
	 	while (hay_celdas){
			if (!tab.Elemento(fil,col).marcada){
				Aniadir(aux, fil, col);
	 			Abrir(fil,col);
				Extraer(pend);
			}
		 	if (MinasProximas(fil, col) == 0 ){
				for (int i=fil-1; i <= fil+1; i++){
					for (int j=col-1; j <= col+1; j++){
						celda.fila = i; celda.columna = j; 
						if (tab.PosicionCorrecta(i,j) && !tab.Elemento(i,j).bomba 
							&& !tab.Elemento(i,j).marcada && !BuscarCelda(aux, celda)){
							 Aniadir(pend, i, j);
							 Aniadir(aux, i, j);
						}
					}
				}
		 	}
			if (pend == 0)
				hay_celdas = false;
			else{
	  			fil = pend -> fila;
	 			col = pend -> columna;	
			}
		}
		Liberar(pend);
		Liberar(aux);
	}
}
