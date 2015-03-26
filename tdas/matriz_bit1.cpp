#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
#include <iostream>
using namespace std;


bool Leer(const char nombre[],MatrizBit& m);
bool Escribir(const char nombre[], const MatrizBit& m);
void Traspuesta(MatrizBit& res,const MatrizBit& m);
void And(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2);
void Or(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2);
void Not(MatrizBit& res,const MatrizBit& m);
