#ifndef buscaminas_h
#define buscaminas_h

#include <iostream>
using namespace std;

struct Casilla{
		bool bomba, abierta, marcada;	
};

class Tablero{
private: 
	Casilla *datos;
	int filas, columnas;
public:
	Tablero();
	Tablero(const Tablero &tab);
	~Tablero();
   void Inicializar(int fil, int col);
	inline int Filas() const;
	inline int Columnas() const;
	Casilla Elemento(int fil, int col) const; // Deprecated
	Casilla& operator()(int fil, int col);
	const	Casilla& operator()(int fil, int col) const;
	void Modificar(int fil, int col, bool bom, bool ab, bool marc);
	void InsertarMinas(int min);
	void CambiarMarca(int f, int c);
	void Abrir(int f, int c);
	bool PosicionCorrecta(int i, int j) const;
};

class CampoMinas{
private: 
	Tablero tab;
	int MinasProximas(int fil, int col) const;
	void ImprimeCasilla(int n) const;
	bool explosion;
public:
	CampoMinas(int filas, int columnas, int min);
	CampoMinas(CampoMinas &campo);
	~CampoMinas();
	CampoMinas& operator=(CampoMinas &tablero);
	inline int Filas() const;
	inline int Columnas() const;
	bool Explosionado() const;
	bool Ganado() const;
	bool Marcar(int fil, int col);
	bool Abrir(int fil, int col);
	void PrettyPrint(std::ostream &os=std::cout);
	void RevelarTablero() const;
	void PulsarBoton(int f, int c);
};
#endif
