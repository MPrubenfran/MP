#include "matriz_bit.h" // Aquí se define el valor de CUAL_COMPILO
#include <iostream>
#include <string>
#include <fstream>
using namespace std
/////////////////////////////////////////////////////////////////////////////////////////////////matriz_bit.cpp
bool Inicializar (MatrizBit& m, int fils, int cols){
bool inicializar = true;
if( (fils != m.filas) || (cols != m.columnas) )
inicializar = false;
if (inicializar){
for (int i=0; i<10; i++){
for (int j=0; j<10; j++){
m.matriz[i][j] = 0;
}
}
}
return inicializar;
}
int Filas (const MatrizBit& m){
  return (m.dimension >> 16);
}
int Columnas (const MatrizBit& m){
  return ((m.dimension << 16) >> 16);
}
bool Get(const MatrizBit& m,int f,int c){
if ( (f<m.filas) && (c<m.columnas) )
return m.matriz[f][c];
else
return 0;
}
void Set(MatrizBit& m, int f,int c,bool v){
if ( (f < m.filas) && (c < m.columnas) )
m.matriz[f][c] = v;
}
/////////////////////////////////////Resto de funcinoes
bool Leer(std::istream& is, MatrizBit& m){
bool exito = true;
int filas= m.filas, columnas= m.columnas;
char booleano;
if (is.fail())
exito = false;
else{
if (is.peek() < 11){ // 1
is >> m.filas;
if (is.peek() < 11){
is >> m.columnas;
// Lectura1(); //true: éxito
//////////////////////////////////////
if (! is.fail() ){
for (int i=0; i< m.filas; i++){
for (int j=0; j< m.columnas; j++)
is >> m.matriz[i][j];
}
}
}
else
exito= false;
}
else if (is.peek() == 'X' || is.peek() == '.'){ // 2
int i=0, j;
char caracter;
while (is.peek() == 'X' || is.peek() == '.'){
j=0;
while(is.peek() != '\n' && is.peek() != '\t'){
is >> caracter;
if (caracter == 'X')
m.matriz[i][j] = true;
else
m.matriz[i][j] = false;
j++;
}
if (i == 0)
m.columnas = j;
i++;
while ( (is.peek() == '\n') || (is.peek() == '\t') || (is.peek() == ' ') )
is.get(caracter); // Controlamos la entrada de datos saltando línea
}
m.filas =i;
}
//Lectura2(); //true: éxito
else // 3
exito = false;
}
return exito;
}
bool Escribir(std::ostream& os,const MatrizBit& m){
bool exito = true;
os << m.filas << " " << m.columnas << endl;
for (int i=0; i< m.filas; i++){
for (int j=0; j< m.columnas; j++)
os << m.matriz[i][j];
}
return exito;
}
bool Leer(const char nombre[],MatrizBit& m){
ifstream is(nombre);
bool exito = Leer(is, m);
return exito;
}
bool Escribir(const char nombre[], const MatrizBit& m){
ofstream os(nombre);
bool exito= Escribir(os, m);
return exito;
}
void Traspuesta(MatrizBit& res,const MatrizBit& m){
res.filas = m.columnas,
res.columnas = m.filas;
for (int i=0; i< res.filas; i++){
for (int j=0; j< res.columnas; j++)
res.matriz[i][j] = m.matriz[j][i];
}
}
void And(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2){
if ( (m1.filas == m2.filas) && (m1.columnas == m2.columnas) ){
res.filas = m1.filas;
res.columnas = m1.columnas;
for (int i=0; i< res.filas; i++){
for (int j=0; j< res.columnas; j++){
if ( (m1.matriz[i][j] == false) || (m2.matriz[i][j] == false) ) // 0 false; 1 true;
res.matriz[i][j] = false;
else
res.matriz[i][j] = true;
}
}
}
}
void Or(MatrizBit& res,const MatrizBit& m1,const MatrizBit& m2){
if ( (m1.filas == m2.filas) && (m1.columnas == m2.columnas) ){
res.filas = m1.filas;
res.columnas = m1.columnas;
for (int i=0; i< res.filas; i++){
for (int j=0; j< res.columnas; j++){
if ( (m1.matriz[i][j] == true) || (m2.matriz[i][j] == true) ) // 0 false; 1 true;
res.matriz[i][j] = true;
else
res.matriz[i][j] = false;
}
}
}
}
void Not(MatrizBit& res,const MatrizBit& m){
if ( (m1.filas == m2.filas) && (m1.columnas == m2.columnas) ){
res.filas = m1.filas;
res.columnas = m1.columnas;
for (int i=0; i< res.filas; i++){
for (int j=0; j< res.columnas; j++)
res.matriz[i][j] = ! m.matriz[i][j];
}
}
}
