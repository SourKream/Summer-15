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
	std::string fileName;		// <Genome Name>_<Window Size>_<Sub-Window Size>
	std::string genomeName; 	// <Genome Name>
	bool debug;
	bool correlateMode; // true: CrossCorrelate false: autoCorrelate
	std::vector<float> plotValues;
	
	 float AutoCorrelate (float [], int);
	 float CrossCorrelate(float [],int);
	 float Entropy (int);
	 float CorrelatedEntropy();
	 float Correlate (int k, float seq[], int N,const float &meanx,const float meany,const float &variance);
	std::string currWindow;
public:

	Cem(int ,int);
	Cem();
	void setWinSubWin(int,int);
	void operate(const std::string &);
	void write(const std::string &);
	std::string getFileName();
	std::string getGenomeName();
	void setDebugFlag();
	void setCorrelatedModeFlag();
	bool getCorrelatedModeFlag();
};

#endif 