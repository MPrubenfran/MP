#ifndef matrizbit1_h
#define matrizbit1_h

#include <iostream>
#include "MatrizBit.h"
using namespace std;

struct MatrizBit{
	int filas, columnas;
	bool matriz[10][10];
};


bool Leer(std::istream& is, MatrizBit& m);
bool Escribir(std::ostream& os,const MatrizBit& m);
bool Leer(const char nombre[],MatrizBit& m);
bool Escribir(const char nombre[], const MatrizBit& m);
void Traspuesta(MatrizBit& res,const MatrizBit& m);
void And(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2);
void Or(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2);
void Not(MatrizBit& res,const MatrizBit& m);



#endif
