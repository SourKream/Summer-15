#include "gcskew.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc,char* argv[]){
	if(argc!=4){
		cout << "\nSyntax: ./GCSKEW.o <File_Name> <Window_Size> <Debug_State>\n\n";
		return 1;
	}
	int winSize=atoi(argv[2]),debugValue=atoi(argv[3]);
	GcSkew a(winSize);
	if(debugValue){
		a.setDebugFlag();
	}

	a.operate(argv[1]);
	a.write("");

	
	system("gnuplot Source/plot.plt");
	
	string command = "mv Plots/Plot.svg Plots/GCSkew/GC_" + a.getFileName() + ".svg";
	system(command.c_str());
	command = "mv Data/GenomeData.txt Data/GCSkew/GC_" + a.getFileName() + ".txt";
	system(command.c_str());

	cout << "Output Generated: GCSkew/GC_" << a.getFileName() << ".svg\"\n\n";


	return 0;
}

