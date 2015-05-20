#include "cem.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(int argc,char* argv[]){
	if(argc!=4){
		cout << "\nSyntax: ./CEM.o <File_Name> <Window_Size> <SubWindow_Size>\n\n";
		return 1;
	}
	int winSize=atoi(argv[2]),subWinSize=atoi(argv[3]);
	if(winSize<subWinSize){
		cout<<"\n Window size is less than subwindow size. Error \n\n";
		return 1;
	}
	Cem a(winSize,subWinSize);

	// Cem a(50000,125);
	// string inp;
	// cout<<"Enter file name: ";
	// cin>>inp;
	//Give input as Data/Genome.txt
	a.operate(argv[1]);
	a.write("");


	// Plotting the Data in GenomeData.txt and saving it in Plots/ after renaming
	system("gnuplot Source/plot.plt");

	string command = "mv Plots/Plot.svg Plots/" + a.getFileName() + ".svg";
	system(command.c_str());
	command = "mv Data/GenomeData.txt Data/" + a.getFileName() + ".txt";
	system(command.c_str());

	cout << "Output Generated: " << a.getFileName() << ".svg\"\n\n";

return 0;
}