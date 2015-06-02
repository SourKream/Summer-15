#include "gcskew.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc,char* argv[]){
	if(argc!=4){
		cout << "\nSyntax: ./GCSKEW.o <File_Name> <Window_Size> <Debug_State>\n\n";
		int winSize=atoi(argv[2]),debugValue=atoi(argv[3]);
		return 1;
	}
	GcSkew a(winSize);
	if(debugValue){
		a.setDebugFlag();
	}

	a.operate(argv[1]);
	a.write("");

	
	system("gnuplot Source/plot.plt");
	string folderExtension = ( a.getCorrelatedModeFlag() )? "CrossCorrelate":"AutoCorrelate";
	
	string command = "mv Plots/Plot.svg Plots/" + folderExtension + a.getFileName() + ".svg";
	system(command.c_str());
	command = "mv Data/GenomeData.txt Data/" + folderExtension + a.getFileName() + ".txt";
	system(command.c_str());

	cout << "Output Generated: " << a.getFileName() << ".svg\"\n\n";


	return 0;
}

