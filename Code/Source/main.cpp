#include "cem.hpp"
#include <iostream>
#include <string>
using namespace std;

int main(){
Cem a(50000,125);
string inp;
cout<<"Enter file name: ";
cin>>inp;
//Give input as Data/Genome.txt
a.operate(inp);
a.write("");
return 0;
}