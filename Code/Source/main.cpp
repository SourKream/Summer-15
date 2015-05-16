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
return 0;
}