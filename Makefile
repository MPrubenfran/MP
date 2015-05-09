CXXFLAGS= -Wall -Wextra -pedantic -std=c++03 -g
LIBS= -L./lib -lminas

INCLUDE= ./include
BIN=./bin
DIR_LIBS=./lib
SRC=./src
OBJ=./obj

all: buscaminas

buscaminas: $(OBJ)/main.o $(OBJ)/buscaminas.o
	g++ -o $(BIN)/$@ $^ 

$(OBJ)/buscaminas.o: $(SRC)/buscaminas.cpp $(INCLUDE)/buscaminas.h 
	g++ -c -I$(INCLUDE) $(CXXFLAGS) -o $@ $<

$(OBJ)/main.o: $(SRC)/main.cpp 
	g++ -c -I$(INCLUDE) $(CXXFLAGS) -o $@ $<

clean: 
	@ echo "Limpiando ..."
	rm -f $(OBJ)/*.o $(OBJ)/*~ $(SRC)/*~ $(INC)/*~ $(BIN)/*~ *~ 

mrproper: clean
	rm -f $(BIN)/*

.PHONY: clean mrproper all
