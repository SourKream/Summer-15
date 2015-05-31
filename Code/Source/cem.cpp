#ifndef CEM_CPP
#define CEM_CPP
#include "cem.hpp"

#define SHIFT_FRACTION 1 //Defining by what fraction is the window sliding. Taken to be 1/5th by default.

std::string Cem::getFileName(){
	return fileName;
}

Cem::Cem(int winSize,int subwinSize){
	windowSize = winSize;
	subWindowSize = subwinSize;
	numSubWindows = windowSize / subWindowSize;
	if (windowSize % subWindowSize)
		numSubWindows++;
	shiftFraction = SHIFT_FRACTION;
}


Cem::Cem(){
	shiftFraction = SHIFT_FRACTION;
}


void Cem::setWinSubWin(int winSize,int subWinSize){
	windowSize = winSize;
	subWindowSize = subWinSize;
	numSubWindows = windowSize / subWindowSize;
	if (windowSize % subWindowSize)
		numSubWindows++;
}


float Cem::Entropy (int subWindowStartIndex){
	int subwindowLength = std::min(subWindowSize,((int)currWindow.length() - subWindowStartIndex));
	int freqA = 0, freqT = 0, freqC = 0, freqG = 0;
	for(int i=0; i<subwindowLength; i++){		// count number of times each base is present in the subwindow
		switch (currWindow[i + subWindowStartIndex]){
			case 'A': freqA++;
					 break;
			case 'T':freqT++;
					 break;
			case 'C':freqC++;
					 break;
			case 'G':freqG++;
					 break;
			default: break;
		}
	}
	
	float probA = (((float)freqA/subwindowLength) == 0.0) ? 1 : ((float)freqA/subwindowLength);	// probability of occurence of each base if prob==0 then prob=1, so that log(prob) is defined.
	float probT = (((float)freqT/subwindowLength) == 0.0) ? 1 : ((float)freqT/subwindowLength);
	float probC = (((float)freqG/subwindowLength) == 0.0) ? 1 : ((float)freqG/subwindowLength);
	float probG = (((float)freqC/subwindowLength) == 0.0) ? 1 : ((float)freqC/subwindowLength);
	float entropy = 0; 
	
	entropy += probA * log2 (probA);	// As per the entropy formula
	entropy += probT * log2 (probT);
	entropy += probC * log2 (probC);
	entropy += probG * log2 (probG);
	entropy = -entropy;
	
	return entropy;
}


float Cem::CorrelatedEntropy(){
	long windowLength = currWindow.length();				// The last window maybe smaller than the windowSize chosen
	float *entropySequence = new float[numSubWindows];			// Array to store the sequence of entropy values of each subwindow

	for(int i=0;i<numSubWindows;i++)
		entropySequence[i] = 0.0;
	
	int i;
	for (i=0; i*subWindowSize<windowLength; i++){
		entropySequence[i] = Entropy(i*subWindowSize);						// and its entropy value stored in array
	}
	
	return AutoCorrelate(entropySequence, i);		// Autocorrealtion is applied on the array
													// and the resulting correlated entropy measure of the
													// window is returned
}


float Correlate (int k, float seq[], int N,const float &mean,const float &variance){ // Subfunction of autocorrelation function
	float Ck = 0;
	for (int i=0; i<N-k; i++)
		Ck += (seq[i] - mean)*(seq[i+k] - mean);
	
	Ck /= (N-k);
	if(variance!=0)
		Ck /= (variance);
	return Ck;
}


float Cem::AutoCorrelate (float seq[], int N){ // Standard Autocorrelation function
	float seqMean =0, seqVariance =0;
	for (int i=0; i<N; i++){		// To find the mean and sigma(xi*xi)  of the sequence
		seqMean += seq[i];
		seqVariance += seq[i]*seq[i];
		
	}
	seqMean /= N;
	
	seqVariance  = (seqVariance / N) - seqMean*seqMean; // Variance  = (1/N*sigma(xi*xi)) - (x bar)^2;
	/*for(int i=0;i<N;i++){
		seqVariance+=(seq[i] - seqMean)*(seq[i] - seqMean);
	}*/
	//seqVariance /= N;
	float CorrelatedValue = 0;
	
	for (int i=1; i<N; i++)
		CorrelatedValue += fabs(Correlate(i, seq, N, seqMean, seqVariance));
	
	CorrelatedValue /= (N-1);
	
	return CorrelatedValue;
}

void Cem::operate(const std::string& src){
	std::fstream f;
	f.open(src,std::ios::in);
	float shiftMargin = 1.0 - shiftFraction;
	if(!f){
		std::cout<<"Error while opening file \n";
		return;
	}

	fileName = src.substr(src.find_last_of('/')+1);
	fileName = fileName.substr(0,fileName.find_last_of('.'));
	fileName += "_" + std::to_string(windowSize) + "_" + std::to_string(subWindowSize);

	getline(f,currWindow); //Skipping the first line
	//std::cout<<currWindow<<"\n";
	while(!f.eof()){
		currWindow = "";
		for(int i=0;i<windowSize && !f.eof();++i){
			char mTmp = f.get();
			if((mTmp>='A' && mTmp<='Z') || (mTmp>='a' && mTmp<='z'))
				currWindow+=mTmp;
			else 
				i--;
		}
		plotValues.push_back(CorrelatedEntropy());
		if(!f.eof()){
			f.seekg(-shiftMargin * windowSize * sizeof(char),std::ios::cur); // For overlapping windows.
		}
	}
	f.close();
}

void Cem::write(const std::string &dest){
	/*for(int i=0;i<plotValues.size();++i){
		std::cout<<i+1<<" : "<<plotValues[i]<<"\n";
	}*/
	std::fstream filOut;
	filOut.open("Data/GenomeData.txt",std::ios::out);
	for(int i=0;i<plotValues.size();i++){
		filOut<<plotValues[i]<<"\n";
	}
}

#endif