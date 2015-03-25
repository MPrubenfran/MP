

using namespace std;

bool Inicializar (MatrizBit& m, int fils, int fils, int cols);
int Filas (const MatrizBit& m);
int Columnas (const MatrizBit& m);
bool Get(const MatrizBit& m,int f,int c);
void Set(MatrizBit& m,int f,int c,bool v);
bool Leer(std::istream& is,MatrizBit& m);
bool Escribir(std::ostream& os,const MatrizBit& m);
bool Leer(const char nombre[],MatrizBit& m);
bool Escribir(const char nombre[], const MatrizBit& m);
void Traspuesta(MatrizBit& res,const MatrizBit& m);
void And(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2);
void Or(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2);
void Not(MatrizBit& res,const MatrizBit& m);
