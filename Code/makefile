SRC=Source/
OBJ=Obj/
DATA=Data/
EXE=cem.out
GEXE=gcskew.out
COMPILER=g++ -std=c++11
FNAME="Genome/Genome.txt"
WINSIZE=50000
SUBWINSIZE=125
DEBUG=0
MODE=0
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
	rm $(EXE) $(GEXE)
	rm $(OBJ)*

execute:$(EXE)
	./$(EXE) $(FNAME) $(WINSIZE) $(SUBWINSIZE) $(DEBUG) $(MODE)

gcskew:$(GEXE)
	./$(GEXE) $(FNAME) $(WINSIZE) $(DEBUG)

$(GEXE): $(OBJ)gcskew.o $(OBJ)mainGcSkew.o
	$(COMPILER) $^ -o $@

$(OBJ)gcskew.o:$(SRC)gcskew.cpp $(SRC)gcskew.hpp
	$(COMPILER) -c $<
	mv gcskew.o $@

$(OBJ)mainGcSkew.o:$(SRC)mainGcSkew.cpp
	$(COMPILER) -c $<
	mv mainGcSkew.o $@
