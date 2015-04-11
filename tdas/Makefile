# Con un código tan simple, usemos un makefile simplificado
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++03 -pedantic -g

# ************ Generación de ejecutable ************

calcular: matriz_bit.h matriz_bit.cpp matriz_operaciones.h matriz_operaciones.cpp matriz_bit1.h matriz_bit1.cpp calcular.cpp
	$(CXX) $(CXXFLAGS) -o calcular matriz_bit.cpp matriz_operaciones.cpp calcular.cpp

# ************ Limpieza ************
clean :
	-rm calcular ./*~ ./*.o
