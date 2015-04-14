#ifndef matrizbit4_h
#define matrizbit4_h

#include <iostream>
using namespace std;

struct MatrizBit{
  unsigned int matriz[4]; // 32*4=128 bits.
  unsigned short int dimension; // 8(filas)+8(columnas) bits
};

#endif
