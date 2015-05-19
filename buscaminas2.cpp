/**
  * @file buscaminas.cpp
  *
  */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <cassert>
#include <iomanip>
#include <cstring>
#include "buscaminas.h"
using namespace std;

#define RESET       "\x1b[0m"
#define ROJO        "\x1b[31m"
#define VERDE       "\x1b[32m"
#define AMARILLO    "\x1b[33m"
#define AZUL        "\x1b[34m"
#define BLANCO      "\x1b[37m"
#define NEGRO       "\x1b[30m"
#define NEGRITA_ON  "\x1b[1m"

namespace{
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

bool BuscarCelda (CeldaPosicion *&p, const CeldaPosicion &celda){
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

}

ostream& operator << (std::ostream& os, const Casilla& cas){
	os << cas.bomba << cas.abierta << cas.marcada;
	return os;
}

istream& operator >> (std::istream& is, Casilla& cas){
	is >> cas.bomba >> cas.abierta >> cas.marcada;
	return is;
}

Tablero::Tablero() :datos(0),filas(0),columnas(0){}

Tablero::Tablero(const Tablero &tab){
	int fil = tab.Filas(), col = tab.Columnas();
	filas = fil;
	columnas = col;

	if (filas !=0 && columnas != 0)
		datos = new Casilla[fil*col];
	else
		datos = 0;
	for (int i=0; i<fil; i++){
		for (int j=0; j<col; j++)
			datos[i*col+j] = Elemento(i,j);
	}
}

Tablero::~Tablero(){
	filas = columnas = 0;
	delete [] datos;
	datos = 0;
}

void Tablero::Inicializar(const int& fil, const int& col){
  if (fil > 0 && col > 0){
	filas = fil;
	columnas = col;
	datos = new Casilla[fil*col];
  }
  else{
	filas = columnas = 0;
	datos = 0;
  }
}

int Tablero::Minas()const{
   int min=0;
   for (int i=0;i<filas; i++){
      for (int j=0;j<columnas; j++){
         if (datos[i*columnas+j].bomba)
            min++;
      }
   }
   return min;
}

Casilla Tablero::Elemento(const int& fil, const int& col) const{ // Deprecated
  assert(PosicionCorrecta(fil, col));
  return datos[fil*columnas+col];
}

Casilla& Tablero::operator()(const int& fil, const int& col){
   assert(PosicionCorrecta(fil, col));
	return datos[fil*columnas + col];
}

const Casilla& Tablero::operator()(const int& fil, const int& col) const{
   assert(PosicionCorrecta(fil, col));
	return datos[fil*columnas + col];
}

Tablero& Tablero::operator =(const Tablero &tab){
	if (this != &tab){
		delete [] datos;
		filas = tab.Filas();
		columnas = tab.Columnas();
		datos = new Casilla[filas*columnas];
		for (int i=0; i<filas; i++){
			for (int j=0; j<columnas; j++)
				datos[i*columnas+j] = tab(i,j);
		}
	}
	return *this;
	// return *(new CampoMinas(tablero));
}

void Tablero::Modificar(const int& fil, const int& col, const bool& bom, const bool& ab, const bool& marc){
   assert( PosicionCorrecta(fil, col) );
   datos[fil*columnas+col].abierta = ab;
   datos[fil*columnas+col].bomba = bom;
   datos[fil*columnas+col].marcada = marc;
}

void Tablero::InsertarMinas(int min){
	int x,y;
	srand(time(NULL));
	while(min > 0){
		x = rand()%filas;
		y = rand()%columnas;
		if (Elemento(x,y).bomba == false){
			datos[x*columnas+y].bomba = true;
			min--;
		}
	}
}

void Tablero::CambiarMarca(const int& f, const int& c){
	if (PosicionCorrecta(f, c))
		datos[f*columnas+c].marcada = !Elemento(f,c).marcada;
	else
		cout << "Error en marcado, posición incorrecta.\n";
}

void Tablero::Abrir(const int& f, const int& c){
	assert(PosicionCorrecta(f, c));
	datos[f*columnas+c].abierta = true;
}

bool Tablero::PosicionCorrecta(const int& f, const int& c) const{
	return (f>=0 && c>=0 && f< filas && c < columnas);
}

ostream& operator << (std::ostream& os, const Tablero& tab){
	int f = tab.Filas(), c = tab.Columnas();
	os << f << " " << c << endl;
	for (int i=0; i<f; i++){
		for (int j=0; j<c; j++)
			os << tab(i,j) << " ";
		os << endl;
	}
	return os;
}

istream& operator >> (std::istream& is, Tablero& tab){
	int f, c;
	bool fallo = false;
	is >> f >> c;
	tab.~Tablero();
	tab.Inicializar(f,c);
	for (int i=0; i<f && !fallo; i++){
		for (int j=0; j<c && !fallo; j++){
			is >> tab(i,j);
			if (is.fail())
				fallo = true;
		}
	}
	return is;
}

int CampoMinas::MinasProximas(const int& fil, const int& col) const{
	int minas=0;
	for (int i=fil-1; i <= fil+1; i++){
		for (int j=col-1; j <= col+1; j++){
			if (tab.PosicionCorrecta(i,j) && tab.Elemento(i,j).bomba)
				minas++;
		}
	}
	return minas;
}

void CampoMinas::ImprimeCasilla(const int& n) const{
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

CampoMinas::CampoMinas(const int& filas, const int& columnas, const int& min){
	tab.Inicializar(filas, columnas);
	tab.InsertarMinas(min);
	explosion = false;
}

bool CampoMinas::Explosionado() const{
	return explosion;
}

bool CampoMinas::Ganado() const{
	bool exito = false;
	if (!explosion){
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

bool CampoMinas::Marcar(const int& fil, const int& col){
	bool exito = true;
	if (tab(fil,col).abierta == false)
		tab.CambiarMarca(fil,col);
	else
		return false;
	return exito;
}

bool CampoMinas::Abrir(const int& fil, const int& col){
	bool exito = false;
	if (!tab.Elemento(fil,col).marcada && !tab.Elemento(fil,col).abierta){
		tab.Abrir(fil, col);
		if (tab.Elemento(fil, col).bomba)
			explosion = true;
		exito = true;
	}
	return exito;
}

void CampoMinas::PrettyPrint(std::ostream &os) const{
	os << " ";
	for (int i=0; i<tab.Columnas(); i++){
		os << setw(3) << i;
		if (i == 9)
			os << " ";
	}

	os << endl;
	for (int i=0; i<tab.Filas(); i++){
		if (i<10)
			os << i << "  ";
		else
			os << i << " ";
		for (int j=0; j< tab.Columnas(); j++){
	        if (tab.Elemento(i,j).abierta == false && tab.Elemento(i,j).marcada == false)
				os << "●  ";
			else if (MinasProximas(i,j) != 0 && tab.Elemento(i,j).abierta && !tab.Elemento(i,j).bomba)
				ImprimeCasilla(MinasProximas(i,j));
	        else if (tab.Elemento(i,j).abierta == false && tab.Elemento(i,j).marcada == true)
				os << ROJO << "⚑  " << RESET;
	        else if (tab.Elemento(i,j).abierta && tab.Elemento(i,j).bomba)
				os << ROJO << NEGRITA_ON  <<"💥  " << RESET;
			else
				os << "○  ";
		}
		os << endl;
	}
	os << endl;
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
				cout << ROJO << NEGRITA_ON  <<"💥  " << RESET;
			else if (MinasProximas(i,j) != 0)
				ImprimeCasilla(MinasProximas(i,j));
			else
				cout << "○  ";
		}
		cout <<endl;
	}
	cout << endl;
}

void CampoMinas::PulsarBoton(int fil, int col){
	CeldaPosicion *pend =0, *aux =0, celda;
	bool hay_celdas = true;
   if (MinasProximas(fil, col) > 0 && !tab.Elemento(fil, col).marcada){
	 	Abrir(fil,col);
	}
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

bool CampoMinas::Leer(const char* archivo){
	bool exito = false;
	ifstream is(archivo);

	if (is){
		char aux[100];
		is.getline(aux, 100);
		if (strcmp(aux,"#MP−BUSCAMINAS−V1") == 0 || strcmp(aux,"#MP−BUSCAMINAS−V2") == 0){
			exito = true;
			is >> tab;
         int f = Filas(), c = Columnas();
         explosion = false;
         for (int i=0; i<f && !explosion;i++){
            for (int j=0; j<c && !explosion; j++){
               if (tab(i,j).bomba && tab(i,j).abierta)
                  explosion = true;
            }
         }
			if (is.fail())
				exito = false;
		}
	}
	is.close();
	return exito;
}

bool CampoMinas::Escribir(const char* archivo) const{
	int exito = false;
	ofstream os(archivo);
	if (os){
		exito = true;
		os << "#MP−BUSCAMINAS−V1" << endl << tab;
		os.close();
	}
   cout << "Guardando partida en \"" << archivo << "\" ..." << endl;
	return exito; // Línea importante.
}

void CampoMinas::Jugar(){
   Accion orden;
   char linea[100];

   while(!Ganado() && !Explosionado()){
      do{
   		cout << "Dime acción y posición o fichero: \n";
         cin.getline(linea, 100);
   		orden = Opcion(&linea[0]);

         if (orden.opcion == 'x')
            cout << "<Orden no reconocida>" << "\t\"" << linea << "\"" << endl;
      }while( orden.opcion != 'a' && orden.opcion != 'm' && orden.opcion != 's' );

   	if (orden.opcion == 'a')
   	   PulsarBoton(orden.fila, orden.columna);
   	else if (orden.opcion == 'm')
   		Marcar(orden.fila, orden.columna);
      else
         Escribir(orden.fichero);

      PrettyPrint();
   }
}

Accion Opcion(const char *linea){
   Accion accion;
   char aux[100], aux_copia[100];
   int contador = 0, i=0, tamanio = strlen(linea);

   for (int i=0; i<tamanio;i++)
      aux_copia[i] = linea[i];
   aux_copia[tamanio] = '\0';

   while( isspace(aux_copia[contador]) )
      contador++;

   if ( isspace(aux_copia[contador+1]) ){
      accion.opcion = tolower(aux_copia[contador]);
      contador++;
   }
   else{
      while ( !isspace(aux_copia[contador+i]) ){ // Copio la primera palabra.
         aux[i] = aux_copia[i+contador];
         i++;
         if( (i+contador) == 100){ // Me aseguro de no salirme del espacio reservado.
            accion.opcion = 'x';
            return accion;
         }
      }
      aux[i] = '\0';
      contador += i;

      if ( strcmp(aux, "abrir") == 0 || strcmp(aux, "Abrir") == 0 )
         accion.opcion = 'a';
      else if ( strcmp(aux, "marcar") == 0 || strcmp(aux, "Marcar") == 0 )
         accion.opcion = 'm';
      else if ( strcmp(aux, "salvar") == 0 || strcmp(aux, "Salvar") == 0 )
         accion.opcion = 's';
      else
         accion.opcion = 'x';
   }

   while( isspace(aux_copia[contador]) )
      contador++;

   i=0;
   while (linea[i+contador] != '\0'){ // Guardo en aux los números o el archivo.
      aux[i] = linea[i+contador];
      i++;
   }
   aux[i] = '\0';
   contador += i;
   tamanio = strlen(aux);
   for (i=0; i<tamanio;i++)
      aux_copia[i] = aux[i];
   aux_copia[i] = '\0';
   if (accion.opcion == 'a' || accion.opcion == 'm'){
      accion.fila = (atoi (strtok(aux_copia," ")) );

      i=0;
      while (isdigit(aux[i]))
         i++;
      while (isspace(aux[i]))
         i++;

      int eje=0;
      while ( !isspace(aux[eje+i]) ){
         aux[eje] = aux[eje+i];
         eje++;
      }
      aux[eje+i] = '\0';
      accion.columna = (atoi (aux));
   }
   else if (accion.opcion == 's'){
      tamanio = strlen(aux);
      while( isspace(aux[tamanio-1]) ){
         aux[tamanio-1] = '\0';
         tamanio--;
      }
      tamanio = strlen(aux);
      if (accion.fichero != 0)
         delete [] accion.fichero;

      accion.fichero = new char[strlen(aux)+1];
      for (int i=0; i<tamanio+1; i++)
         accion.fichero[i] = aux[i];
   }
   return accion;
}

bool Valido(const int& filas, const int& columnas, const int& minas){
   bool booleano = false;
   if (  filas > 0  &&  columnas > 0){
      if (  filas >= 4 || columnas >= 4 ){
         if (  filas*columnas/2 > minas )
            booleano = true;
         else
            cout << "Número de minas incorrecto." << endl;
      }
      else
         cout << "Debe haber al menos 4 filas o 4 columnas." << endl;
   }
   else
      cout << "Error, filas o columnas nulas." << endl;

   return booleano;
}


/*bool CampoMinas::Escribir(char* archivo){
	int exito = false;
	
	ofstream os(archivo);
	if (os) {
		os << "#MP−BUSCAMINAS−V1" << endl;
		tab.filas = fil;
		tab.columnas = col;
		
		for (int i = 0; i < fil; i++){
			for (int j = 0; j < fil; j++){
				os << casilla << " ";
			};
			os << endl;
		}
		
		exito = true;
// (?)		os.close();
	}
	
	return exito;
}
*/
