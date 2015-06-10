#include "cem.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc,char* argv[]){
	if(argc!=6){
		cout << "\nSyntax: ./cem.out <File_Name(FNAME)> <Window_Size(WINSIZE)> <SubWindow_Size(SUBWINSIZE)> <Debug_State(DEBUG)> <Correlation_mode(MODE)>\n\n";
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

	string folderExtension = (a.getCorrelatedModeFlag())? "CrossCorrelate/":"AutoCorrelate/";
	string fileExtension = (a.getCorrelatedModeFlag())? "CC_":"AC_"; 
	string filePath = "Genome/" + a.getGenomeName() + "/" + folderExtension + fileExtension + a.getFileName() + ".txt";
	a.write(filePath);

// Plotting the Data in GenomeData.txt and saving it in Plots/ after renaming
//	system("gnuplot Source/plot.plt");
//	string command = "mv Plots/Plot.svg Plots/" + folderExtension + fileExtension + a.getFileName() + ".svg";
//	system(command.c_str());
//	command = "mv Data/GenomeData.txt Data/" + folderExtension + fileExtension + a.getFileName() + ".txt";
//	system(command.c_str());

	cout << "Output Generated: Genome/" << a.getGenomeName() << "/" << folderExtension << fileExtension << a.getFileName() << ".txt\"\n\n";

return 0;
}