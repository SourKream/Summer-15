#ifndef GC_SKEW_HPP
#define GC_SKEW_HPP
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>

class GcSkew{
	int windowSize;
	float shiftFraction;
	std::string fileName;
	std::string genomeName;
	bool debug;
	std::vector<float> plotValues;
	std::string currWindow;
	float gcSkewEvaluate();
public:
	GcSkew(int);
	GcSkew();
	void operate(const std::string &);
	void write(const std::string &);
	std::string getFileName();
	std::string getGenomeName();
	void setDebugFlag();
	void setWindowSize(int);
};
#endif