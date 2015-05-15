#ifndef CEM_HPP
#define CEM_HPP
#include <vector>

class Cem
{
	int windowSize;
	int subWindowSize;
	int numSubWindows;
	float shiftFraction;
	
	std::string currWindow;
	std::vector<float> plotValues;
	
	float AutoCorrelate (float [], int);
	float Entorpy (int);
	float CorrelatedEntropy();

public:

	Cem(int ,int);
	Cem();
	void setWinSubWin(int,int);
	void operate(const std::string &);
	void write(const std::string &);
};

#endif 