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
	debug=false;
	correlateMode=false;
}


Cem::Cem(){
	shiftFraction = SHIFT_FRACTION;
	debug=false;
	correlateMode=false;
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
	
	if(debug){
		std::cout<<"SUBWINDOW: "<<" ";
	}
	
	for(int i=0; i<subwindowLength; i++){		// count number of times each base is present in the subwindow
		if(debug){
			std::cout<<currWindow[i+ subWindowStartIndex];
		}
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
	if(debug){
		std::cout<<" ";
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
	
	if(debug){
		std::cout<<"Entropy: "<<entropy<<"\n";
	}
	
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
	if(correlateMode){
		return CrossCorrelate(entropySequence,i);  		//Cross Correlation is applied on the array
	}
	else{		
		return AutoCorrelate(entropySequence, i);		// Autocorrealtion is applied on the array
														// and the resulting correlated entropy measure of the
														// window is returned
	}
}


float Cem::Correlate (int k, float seq[], int N,const float &meanx,const float meany,const float &variance){ // Subfunction of autocorrelation function
	float Ck = 0;
	for (int i=0; i<N-k; i++)
		Ck += (seq[i] - meanx)*(seq[i+k] - meany);
	
	Ck /= (N-k);
	if(variance!=0)
		Ck /= (variance);
	
	if(debug){
		std::cout<<"Ck's"<<Ck<<"\n";
	}
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
	
	float CorrelatedValue = 0;
	
	for (int i=1; i<N; i++)
		CorrelatedValue += fabs(Correlate(i, seq, N, seqMean, seqMean, seqVariance));
	
	CorrelatedValue /= (N-1);
	if(debug){
		std::cout<<"Correlated value: "<<CorrelatedValue<<"\n";
	}
	
	return CorrelatedValue;
}

float Cem::CrossCorrelate(float seq[],int N){ // Cross Correlation function, taking a_0,a_1....a_N-k-1 and a_k,a_k+1...a_N-1 as two different sequences
	float CorrelatedValue = 0;
	
	for (int i=1; i<N; i++){
		float seqVariance = 0.0;
		float meanx=0,meany=0,stdx=0,stdy=0;
		for(int j=0;j<N-i;j++){
			meanx+=seq[j];
		}
		for(int j=i;j<N;j++){
			meany+=seq[j];
		}
		meanx = meanx / (N-i);
		meany = meany / (N-i);
		for(int j=0;j<N-i;j++){
			stdx += (seq[j] - meanx)*(seq[j] - meanx);
		}
		for(int j=i;j<N;j++){
			stdy += (seq[j] - meany)*(seq[j] - meany);
		}
		stdx /= (N-i);
		stdy /= (N-i);
		
		stdx = sqrt(stdx);
		stdy = sqrt(stdy);
		seqVariance = stdx*stdy;
		CorrelatedValue += fabs(Correlate(i, seq, N, meanx, meany, seqVariance));
	}
	CorrelatedValue /= (N-1);
	
	if(debug){
		std::cout<<"Correlated value: "<<CorrelatedValue<<"\n";
	}
	
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
	
	int count=0;
	std::string firstWindow="";
	while(!f.eof()){
		currWindow = "";
		int i;
		for( i=0;i<windowSize && !f.eof();++i){
			char mTmp = f.get();
			if((mTmp>='A' && mTmp<='Z') || (mTmp>='a' && mTmp<='z'))
				currWindow+=mTmp;
			else 
				i--;
		}
		if(debug){
			int parse=1;
			for(int i=0;i<100;i++)
				std::cout<<".";
			std::cout<<"\nWINDOW: "<<"\n";
			for (auto it=currWindow.begin();it!=currWindow.end();++it,parse++){
				std::cout<<*it;
				if(parse%subWindowSize==0)
					std::cout<<"\n";
			}
		}
		if(count==0){
			count++;
			//Storing the first window for wrap around, if required
			firstWindow=currWindow;
		}
		if(i<windowSize && currWindow!=""){
			//Updating the last window with wrap around genome data...
			currWindow+=firstWindow.substr(0,windowSize-i);
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

void Cem::setDebugFlag(){
	debug = true;
}

void Cem::setCorrelatedModeFlag(){
	correlateMode = true;
}

bool Cem::getCorrelatedModeFlag(){
	return correlateMode;
}
#endif