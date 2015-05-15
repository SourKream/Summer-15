#ifndef CEM_HPP
#define CEM_HPP
#include <vector>
class Cem{
	int windowSize;
	int subWindowSize;
	int numSubWindows;
	float shiftValue;
	
	std::string currString;
	std::vector<float> plotValues;
	
	void AutoCorrelate();
	void Entorpy();
	void CorrelatedEntropy();
public:
	Cem(int ,int);
	Cem();
	void setWinSubWin(int,int);
	void read(const std::string &);
	void write(const std::string &);

};

#endif 