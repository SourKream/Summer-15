#include "cem.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc,char* argv[]){
	if(argc!=6){
		cout << "\nSyntax: ./CEM.o <File_Name> <Window_Size> <SubWindow_Size> <Debug_State> <Correlation_mode>\n\n";
		return 1;
	}
	int winSize=atoi(argv[2]),subWinSize=atoi(argv[3]),debugValue=atoi(argv[4]),correlationValue = atoi(argv[5]);
	
	if(winSize<subWinSize){
		cout<<"\n Window size is less than subwindow size. Error \n\n";
		return 1;
	}
	Cem a(winSize,subWinSize);
	if(debugValue){
		a.setDebugFlag();
	}
	if(correlationValue){
		a.setCorrelatedModeFlag();
	}

	a.operate(argv[1]);
	a.write("");

	
	// Plotting the Data in GenomeData.txt and saving it in Plots/ after renaming
	system("gnuplot Source/plot.plt");
	string folderExtension = ( a.getCorrelatedModeFlag() )? "CrossCorrelate":"AutoCorrelate";
	
	string command = "mv Plots/Plot.svg Plots/" + folderExtension + a.getFileName() + ".svg";
	system(command.c_str());
	command = "mv Data/GenomeData.txt Data/" + folderExtension + a.getFileName() + ".txt";
	system(command.c_str());

	cout << "Output Generated: " << a.getFileName() << ".svg\"\n\n";

return 0;
}