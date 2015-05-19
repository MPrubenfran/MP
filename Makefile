CXXFLAGS= -Wall -Wextra -pedantic -std=c++03 -g

INCLUDE= ./include
BIN=./bin
DIR_LIBS=./lib
SRC=./src
OBJ=./obj

all: buscaminas

# ************ Compilación de módulos ************
buscaminas: $(OBJ)/main.o $(OBJ)/buscaminas.o
	g++ -o $(BIN)/$@ $^

$(OBJ)/buscaminas.o: $(SRC)/buscaminas.cpp $(INCLUDE)/buscaminas.h
	g++ -c -I$(INCLUDE) $(CXXFLAGS) -o $@ $<

$(OBJ)/main.o: $(SRC)/main.cpp
	g++ -c -I$(INCLUDE) $(CXXFLAGS) -o $@ $<

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************
clean:
	@ echo "Limpiando ..."
	rm -f $(OBJ)/*.o $(OBJ)/*~ $(SRC)/*~ $(INCLUDE)/*~ $(BIN)/*~ *~

mrproper: clean
	rm -f $(BIN)/*

.PHONY: clean mrproper all
