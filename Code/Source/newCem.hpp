#ifndef NCEM_HPP
#define NCEM_HPP
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <boost/filesystem.hpp>
#include <pthread.h>
using namespace std;
using namespace boost::filesystem;

class Cem{
	path src;
	path dest;
	bool debug;
	

	float AutoCorrelate(float [],int);
	float Entropy(int,int);
	float Correlate(int k,float seq[], int N,const float &meanx, const float& meany,const float &variance);
	std::string currWindow;
public:
	std::vector<std::vector<float> > plotValues;
	float CorrelatedEntropy(int windowSize,int subWindowSize);
	Cem(std::string source,std::string destination):src(source),dest(destination),plotValues(951,vector<float>(0)){debug=false;};
	void operate(int);
	void write();
	void setDebugFlag();

};
#endif