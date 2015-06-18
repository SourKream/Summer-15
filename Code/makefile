SRC=Source/
OBJ=Obj/
DATA=Data/
EXE=cem.out
EXE2=filestructure.out
EXE3=folderStructure.out
GEXE=gcskew.out
COMPILER=g++ -std=c++11
FNAME=
GENOME=Genome
LIBS=-lboost_filesystem -lboost_system
WINSIZE=50000
SUBWINSIZE=125
DEBUG=0
MODE=0
all:
	make $(EXE)
	make $(EXE2)

$(EXE2): $(OBJ)filestructure.o
	$(COMPILER) $^ -o $@ $(LIBS)

$(OBJ)filestructure.o:$(SRC)filestructure.cpp
	$(COMPILER) -c $< 
	mv filestructure.o $@

$(EXE): $(OBJ)cem.o $(OBJ)main.o
	$(COMPILER) $^ -o $@

$(OBJ)cem.o:$(SRC)cem.cpp $(SRC)cem.hpp
	$(COMPILER) -c $<
	mv cem.o $@

$(OBJ)main.o:$(SRC)main.cpp
	$(COMPILER) -c $<
	mv main.o $@

clean: 
	rm $(OBJ)*
	rm $(EXE) $(EXE2) $(GEXE) 

execute:$(EXE) $(EXE2)
	#./$(EXE2) $(FNAME)
	./$(EXE) $(FNAME) $(WINSIZE) $(SUBWINSIZE) $(DEBUG) $(MODE)

allGCSkew:
	make $(GEXE)

executeGCSkew:$(GEXE)
	./$(GEXE) $(FNAME) $(WINSIZE) $(DEBUG)

$(GEXE): $(OBJ)gcskew.o $(OBJ)mainGcSkew.o
	$(COMPILER) $^ -o $@

$(OBJ)gcskew.o:$(SRC)gcskew.cpp $(SRC)gcskew.hpp
	$(COMPILER) -c $<
	mv gcskew.o $@

$(OBJ)mainGcSkew.o:$(SRC)mainGcSkew.cpp
	$(COMPILER) -c $<
	mv mainGcSkew.o $@

download: script.py
	python $<

allFolderStruct:
	make $(EXE3)

executeFolderStruct:$(EXE3)
	./$(EXE3) $(GENOME)

$(EXE3):$(OBJ)folderStructure.o
	$(COMPILER) $^ -o $@ $(LIBS)

$(OBJ)folderStructure.o:$(SRC)folderStructure.cpp
	$(COMPILER) -c $<
	mv folderStructure.o $@

