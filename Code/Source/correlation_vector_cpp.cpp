#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
using namespace std;

void someFunction(string src,vector<float>& result_vector, int k_max=30){
	fstream f;
	f.open(src, ios::in);
	string notNeeded;
	getline(f,notNeeded);
	unordered_map<char,int> dictionary = {{'A',0},{'T',1},{'G',2},{'C',3}};
	vector<float> single(4,0.0);
	unordered_set<char> allowed = {'A','T','G','C'};
	char collection[16][2] = {{'A','A'},{'A','T'},{'A','G'},{'A','C'},{'T','A'},{'T','T'},{'T','G'},{'T','C'},{'G','A'},{'G','T'},{'G','G'},{'G','C'},{'C','A'},{'C','T'},{'C','G'},{'C','C'}};
	deque<char> mbuffer;
	float frequency_count[30][4][4] = {};
	k_max +=1;
	while(not f.eof()){
		char genotype = f.get();
		if(allowed.find(genotype) != allowed.end()){
			single[dictionary[genotype]]++;
			if(mbuffer.size()<k_max){
				mbuffer.push_back(genotype);
			}
			else if(mbuffer.size()==k_max){
				mbuffer.pop_front();
				mbuffer.push_back(genotype);
			}
			else{
				cout<<"Error! ";
				break;
			}
			for(int i = mbuffer.size() - 2;i >=0 ;i--){
				frequency_count[mbuffer.size()-2-i][dictionary[mbuffer[i]]][dictionary[genotype]]++;
			}
		}
	}
	int total = 0;
	for (auto it = single.begin();it!=single.end();it++)
		total+= (*it);
	for (int i = 0;i<single.size();i++){
		single[i]/= total;
	}
	
	for (int i = 0;i < 30;i++){
		int total = 0;
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				total+= frequency_count[i][j][k];
			}
		}
		float I = 0.0;
		for(int ii=0;ii<16;ii++){
			float p_i_j = frequency_count[i][dictionary[collection[ii][0]]][dictionary[collection[ii][1]]] / total;
			float p_i = single[dictionary[collection[ii][0]]];
			float p_j = single[dictionary[collection[ii][1]]];
			I += (p_i_j * (log(p_i_j) - log(p_i) - log(p_j)) / log(4.0) );
		}
		result_vector.push_back(I);
	}

}


int main()
{
	vector<float> A;
	someFunction("testing.txt",A);

	for (int i=0; i<A.size(); i++)
		cout << A[i] << endl;
}