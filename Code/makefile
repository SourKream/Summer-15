SRC=Source/
OBJ=Obj/
DATA=Data/
EXE=cem.out
COMPILER=g++ -std=c++11
all:
	make $(EXE)

$(EXE): $(OBJ)cem.o $(OBJ)main.o
	$(COMPILER) $^ -o $@

$(OBJ)cem.o:$(SRC)cem.cpp $(SRC)cem.hpp
	$(COMPILER) -c $<
	mv cem.o $@

$(OBJ)main.o:$(SRC)main.cpp
	$(COMPILER) -c $<
	mv main.o $@

clean:
	rm $(EXE)
	rm $(OBJ)*

execute:$(EXE)
	./$(EXE)