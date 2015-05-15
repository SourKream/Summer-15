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
	
	void AutoCorrelate();
	void Entorpy();
	void CorrelatedEntropy();

public:

	Cem(int ,int);
	Cem();
	void setWinSubWin(int,int);
	void operate(const std::string &);
	void write(const std::string &);
};

#endif 