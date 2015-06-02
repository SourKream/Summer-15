#ifndef GC_SKEW_HPP
#define GC_SKEW_HPP

class GcSkew{
	int windowSize;
	float shiftFraction;
	std::string fileName;
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
	void setDebugFlag();
	void setWindowSize();
};
#endif