#ifndef CEM_HPP
#define CEM_HPP
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>
class Cem
{
	int windowSize;
	int subWindowSize;
	int numSubWindows;
	float shiftFraction;
	
	
	std::vector<float> plotValues;
	
	 float AutoCorrelate (float [], int);
	 float Entropy (int);
	 float CorrelatedEntropy();
	std::string currWindow;
public:

	Cem(int ,int);
	Cem();
	void setWinSubWin(int,int);
	void operate(const std::string &);
	void write(const std::string &);
	// float AutoCorrelate (float [], int);
	// float Entropy (int);
	// float CorrelatedEntropy();
	
};

#endif 