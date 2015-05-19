 /**
	* @file buscaminas.h
	* @brief Fichero cabecera para el tratamiento del buscaminas.
	*
	* @author Rubén Morales Pérez
	* @author Francisco Javier Morales Piqueras
	* @date 18/05/2015
	* \note Nos permitirá interactuar con un objeto de la clase CampoMinas.
	*
	* \verbatim
	* 		Este proyecto ha sido desarrollado como práctica final
	* 		de la asignatura "Metodología de la programación"
	* 		del primer curso del doble grado en ingeniería
	* 		informática y matemáticas de la Universidad de Granada.
	* \endverbatim
	*
	*/

#ifndef buscaminas_h
#define buscaminas_h

#include <iostream>
using namespace std;

 /**
	* @struct Casilla
	* @brief Estructura que define una casilla del juego.
	* @see bool
	*
	*/
struct Casilla{
	bool bomba, abierta, marcada;

 /**
	* @brief Inicializador por defecto de la estructura "Casilla".
	* @param Constructor sin parámetros.
	*
	*/
	Casilla():bomba(false),abierta(false),marcada(false){}
};

 /**
	* @brief Salida de flujo para una casilla, valores 0=false/1=true
	* @see fstream
	* @param std::ostream& os
	* @param const Casilla& cas
	* @return ostream&
	* @pre Debes tener permiso de escritura.
	*
	*/
ostream& operator << (std::ostream& os, const Casilla& cas);

 /**
	* @brief Entrada de flujo para una casilla, valores 0=false/1=true
	* @see fstream
	* @param std::istream& is
	* @param Casilla& cas
	* @return istream&
	* @pre (is.fail() == false)
	*
	*/
istream& operator >> (std::istream& is, Casilla& cas);


 /**
	* @class Tablero
	* @brief Clase tablero con las casillas en memoria dinámica.
	* \note Esta clase está contenida en la clase CampoMinas.
	* @see Casilla *datos = new Casilla[filas*columnas];
	*
	*/
class Tablero{
private:
	Casilla *datos;
	int filas, columnas;
public:
 /**
	* @brief Constructor sin parámetros.
	* \note Inicializa datos, filas y columnas a 0.
	*
	*/
	Tablero();

 /**
	* @brief Constructor de copia.
	* @param const Tablero &tab
	* @pre tab correctamente definido.
	*
	*/
	Tablero(const Tablero &tab);

 /**
	* @brief Destructor de la clase.
	* @pre *datos debe apuntar a una posición a cuya memoria tengamos acceso.
	*
	*/
	~Tablero();

 /**
	* @brief Inicializador de la clase.
	* @param int fil
	* @param int col
	* @return void
	* @pre (fil>0 && col>0)
	*
	*/
   void Inicializar(const int& fil, const int& col);

 /**
	* @brief Función inline para conocer las filas del tablero.
	* @see inline function
	* @return int filas > 0
	*
	*/
	int Filas() const{
		return filas;
	}

 /**
	* @brief Función inline para conocer las columnas del tablero.
	* @see inline function
	* @return int columnas > 0
	*
	*/
	int Columnas() const{
		return columnas;
	}

 /**
	* @brief Función inline para conocer las minas del tablero.
	* @see inline function
	* @return int minas > 0
	*
	*/
	int Minas() const;

 /**
	* @brief Devuelve el elemento
	* \note Esta función está obsoleta, se usará
	* @see struct Casilla
	* @param const int& fil
	* @param const int& col
	* @return Casilla
	* @retval Casilla elegida, si no es una posición válida el programa se cerrará.
	* @pre PosicionCorrecta(fil, col)
	*
	*/
	Casilla Elemento(const int& fil, const int& col) const; // Deprecated

 /**
	* @brief Referencia a una Casilla de la clase.
	* \note Uso preferente a la funcion Elemento()
	* @see Devolución por referencia.
	* @param const int& fil
	* @param const int& col
	* @return Casilla&
	* @pre PosicionCorrecta(fil, col)
	*
	*/
	Casilla& operator()(const int& fil, const int& col);

 /**
	* @brief Versión constante de la devolución por referencia.
	* @see 	Casilla& operator()(const int& fil, const int& col);
	*
	*/
	const	Casilla& operator()(const int& fil, const int& col) const;

 /**
	* @brief Operación de asignación definido acorde a la memoria dinámica.
	* @see Devolución por referencia.
	* @param const Tablero &tab
	* @return Tablero&
	* @pre No tiene sentido llamar al operador sobre sí mismo.
	*
	*/
	Tablero& operator=(const Tablero &tab);

 /**
	* @brief Cambia completamente una casilla del tablero.
	* \note ¡Cuidado! Es preferible usar otras funciones más intuitivas.
	* @see void Abrir(int f, int c)
	* @see void CambiarMarca(int f, int c)
	* @see void InsertarMinas(int min)
	* @param const int& fil
	* @param const int& col
	* @param const bool& bom
	* @param const bool& ab
	* @param const bool& mar
	* @return void
	* @pre PosicionCorrecta(fil, col)
	*
	*/
	void Modificar(const int& fil, const int& col, const bool& bom, const bool& ab, const bool& marc);

 /**
	* @brief Define las minas iniciales del tablero.
	* @see bool Valido(int filas, int columnas, int minas);
	* @param const int& min
	* @return void
	* @pre min >= 0
	*
	*/
	void InsertarMinas(int min);

 /**
	* @brief Cambia del booleano de marcado del tablero
	* @see struct Casilla
	* @see bool marcado
	* @param const int& f // fila
	* @param const int& c // columna
	* @return void
	* @pre PosicionCorrecta(f, c)
	*
	*/
	void CambiarMarca(const int& f, const int& c);

 /**
	* @brief Cambia del booleano de abierta del tablero si estaba cerrada.
	* @see struct Casilla
	* @see bool abierta
	* @param const int& f // fila
	* @param const int& c // columna
	* @return void
	* @pre PosicionCorrecta(f, c)
	*
	*/
	void Abrir(const int& f, const int& c);

 /**
	* @brief Informa de los límites de la matriz.
	* @see *datos
	* @param const int& i // fila
	* @param const int& j // columna
	* @return bool
	* @retval true si la posición está dentro de los límites de la matriz.
	* @pre i >= 0  &&  j>= 0
	*
	*/
	bool PosicionCorrecta(const int& i, const int& j) const;
};


 /**
	* @brief Salida de flujo para un Tablero.
	* @see fstream
	* @see ostream& operator << (std::ostream& os, const Casilla& cas);
	* @param std::ostream& os
	* @param const Tablero& tab
	* @return ostream&
	* @pre Debes tener permiso de escritura.
	*
	*/
ostream& operator << (std::ostream& os, const Tablero& tab);

 /**
	* @brief Entrada de flujo para un Tablero.
	* @see fstream
	* @see istream& operator >> (std::istream& is, Tablero& tab);
	* @param std::istream& is
	* @param Tablero& tab
	* @return istream&
	* @pre (is.fail() == false)
	*
	*/
istream& operator >> (std::istream& is, Tablero& tab);


 /**
	* @class Campominas
	* @brief Clase CampoMinas para interactuar con el juego.
	* \note explosion se va actualizando automáticamente cuando abres casillas.
	* @see class Tablero
	*
	*/
class CampoMinas{
private:
	Tablero tab;
	bool explosion; // Casilla abierta y con bomba.
	 /**
		* @brief Contador de las minas que estén en PosicionCorrecta() y a (distancia <= sqrt(2))
		* @param const int& fil
		* @param const int& col
		* @return int
		* @retval 0-9
		* \note Si en la posición hay una bomba también hará el cálculo pero no tendrá sentido.
		* @pre PosicionCorrecta()
		*
		*/
	int MinasProximas(const int& fil, const int& col) const;

	 /**
		* @brief Imprime la casilla si MinasProximas() > 0 && MinasProximas() < 9
		* @see	int MinasProximas(const int& fil, const int& col) const;
		* @param const int& n
		* @return void
		*
		*/
	void ImprimeCasilla(const int& n) const;
public:

	 /**
		* @brief Constructor
		* \note El constructor de copia está definido por defecto al estar definido para cada parámetro.
		* @see
		* @param const int& filas
		* @param const int& columnas
		* @param const int& min
		* \note No hay ambigüedad al pasar un "filas" o "columnas", datos miembro de Tablero.
		*
		*/
	CampoMinas(const int& filas, const int& columnas, const int& min);

	 /**
		* @see int Tablero::Filas() const;
		* \note inline
		* @return int
		*
		*/
	int Filas() const{
		return tab.Filas();
	}

	 /**
		* @see int Tablero::Columnas() const;
		* \note inline
		* @return int
		*
		*/
	int Columnas() const{
		return tab.Columnas();
	}

	 /**
		* @see int Tablero::Minas() const;
		* \note inline
		* @return int
		*
		*/
	int Minas() const{
		return tab.Minas();
	}

	 /**
		* @brief Nos informa si hay una casilla abierta con bomba.
		* @see bool
		* @return bool explosion
		*
		*/
	bool Explosionado() const;

	 /**
		* @brief Comprueba si todas las casillas sin bomba están abiertas.
		* @see
		* @param
		* @return bool
		*
		*/
	bool Ganado() const;

	 /**
		* @brief Marca o desmarca la casilla indicada
		* @see bool Tablero::Marcar(const int& fil, const int& col);
		* @param const int& fil
		* @param const int& col
		* @return bool
		* @retval true si ha tenido éxito
		* @pre Casilla (fil,col) no se ha abierto.
		*
		*/
	bool Marcar(const int& fil, const int& col);

	 /**
		* @brief Abre una casilla de tab
		* @see Tablero tab
		* @param
		* @return bool
		* @retval true si ha abierto la casilla
		* @pre Casilla (fil,col) no se ha abierto.
		*
		*/
	bool Abrir(const int& fil, const int& col);

	 /**
		* @brief Imprime el tablero actual, no puedes ver lo que hay en las casillas cerradas.
		* @param std::ostream &os
		* \note Valor por defecto std::cout
		* @return void
		*
		*/
	void PrettyPrint(std::ostream &os=std::cout) const;

	 /**
		* @brief Revela el tablero cn todas las casillas abiertas menos las que están marcadas.
		* @see void PrettyPrint(std::ostream &os=std::cout) const;
		* @return void
		* @pre Ganado() o Explosionado()
		*
		*/
	void RevelarTablero() const;

	 /**
		* @brief Abre una casilla y las contiguas si no hay bombas cercanas.
		* \note Esta función es iterativa.
		* @see 	bool Abrir(const int& fil, const int& col);
		* @param const int& f
		* @param const int& f
		* @return void
		*
		*/
	void PulsarBoton(int f, int c);

	 /**
		* @brief Lee un CampoMinas de un archivo.
		* @param const char* archivo
		* @return bool
		* @retval true si ha tenido éxito
		* @pre ifstream is(archivo); !is.fail();
		*
		*/
	bool Leer(const char* archivo);

	 /**
		* @brief Escribe un Campominas formateado en un archivo de texto.
		* @see ostream& operator<<(const Casilla& cas);
		* @param const char* archivo
		* @return bool
		* @retval true si ha tenido éxito
		* @pre Debes tener acceso de escritura en el archivo.
		*
		*/
	bool Escribir(const char* archivo) const;

	 /**
		* @brief Hace iteraciones hasta que abras todas las minas o abras una casilla con bomba.
		* @see Marcar() Abrir() Escribir()
		* @return void
		* @pre Debe estar inicializado el tablero.
		*
		*/
	void Jugar();
};

 /**
	* @struct Accion
	* \verbatim
	*	Este struct define una acción para realizar con el CampoMinas.
	* \endverbatim
	* \note si acción es s (salvar) -> fila y columna no tienen sentido, equivalentemente para (a,m)
	* @see
	* @param
	* @return
	* @retval
	* @pre
	*/
struct Accion{
   char opcion; // a (abrir), m (marcar), s (salvar).
   int fila, columna;
	char *fichero; // new char[tamanio]
	 /**
		* @brief Constructor por defecto de la estructura.
		*
		*/
	Accion():opcion('x'),fila(-1),columna(-1),fichero(0){}
};

 /**
	* @brief Recibe una línea leída con getline() y la transforma en una acción.
	* \note Los espacios, tabuladores y saltos de línea no los tiene en cuenta.
	* @see struct Accion
	* @param const char *linea
	* @return Accion
	* \note Accion->opcion estará siempre en minúscula.
	*
	*/
Accion Opcion(const char *linea);

 /**
	* @brief Informa si hay demasiadas minas en el tablero.
	* \note minas>50% -> false
	* @param const int& filas
	* @param const int& columnas
	* @param const int& minas
	* @return bool
	* @retval true si el tablero con los datos planteados es válido.
	* \note No se debe crear un objeto CampoMinas si esta función devuelve false.
	*
	*/
bool Valido(const int& filas, const int& columnas, const int& minas);

#endif
