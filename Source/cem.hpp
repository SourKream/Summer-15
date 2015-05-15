#ifndef CEM_HPP
#define CEM_HPP
#include <vector>
class Cem{
	int windowSize;
	int subwindowSize;
	std::vector<float> plotValues;
	void autoCorrelatedEntropy();
	void entorpy();
	void mLog(float x);
public:
	Cem(int ,int);

};

#endif 