#ifndef NCEM_CPP
#define NCEM_CPP
#include "newCem.hpp"

struct attr{
	int low;int high;int winSize;
	Cem* mObj;
};


float Cem::Entropy (int subWindowStartIndex,int subWindowSize){
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

float Cem::Correlate (int k, float seq[], int N,const float &meanx,const float& meany,const float &variance){ // Subfunction of autocorrelation function
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


float Cem::AutoCorrelate(float seq[],int N){
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

float Cem::CorrelatedEntropy(int windowSize,int subWindowSize){
	long windowLength = currWindow.length();	
	int numSubWindows = windowSize / subWindowSize;
	if (windowSize % subWindowSize)
		numSubWindows++;

	float *entropySequence = new float[numSubWindows];			// Array to store the sequence of entropy values of each subwindow
	for(int i=0;i<numSubWindows;i++)
		entropySequence[i] = 0.0;
	
	int i;
	for (i=0; i*subWindowSize<windowLength; i++){
		entropySequence[i] = Entropy(i*subWindowSize,subWindowSize);						// and its entropy value stored in array
	}

	return AutoCorrelate(entropySequence, i);	
}

void* threadFunction(void* attribute){
	attr* tmp = (attr*) attribute;
	for(int i=tmp->low;i<tmp->high;i++){
		tmp->mObj->plotValues[i-50].push_back(tmp->mObj->CorrelatedEntropy(tmp->winSize,i));
	}
}
void Cem::operate(int windowSize){
	std::fstream f;
	f.open(src.string());
	if(!f){
		std::cout<<"Error in opening file\n";
		return;
	}
	getline(f,currWindow,'\n'); //Skip first line

	int count =0;
	
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
		
		if(count==0){
			count++;
			//Storing the first window for wrap around, if required
			firstWindow=currWindow;
		}
		if(i<windowSize && currWindow!=""){
			//Updating the last window with wrap around genome data...
			currWindow+=firstWindow.substr(0,windowSize-i);
		}
		
		if(debug){
			int parse=1;
			for(int i=0;i<100;i++)
				std::cout<<".";
			std::cout<<"\nWINDOW: "<<"\n";
			for (auto it=currWindow.begin();it!=currWindow.end();++it,parse++){
				std::cout<<*it;
				if(parse%80==0)
					std::cout<<"\n";
			}
		}

		/*START THREAD MAGIC HERE*/
		int numThreads = 30;
		pthread_t* thread = new pthread_t[numThreads];
		attr* attributes = new attr[numThreads];

		int stepSize  = 951 / numThreads;
		for(int i=0;i<numThreads;i++){
			attributes[i].low = (i * stepSize) + 50;
			attributes[i].high = ((i+1)* stepSize) + 50;
			attributes[i].winSize  = windowSize;
			attributes[i].mObj = this;
			pthread_create(&thread[i],NULL,&threadFunction,&attributes[i]);
		}
		for(int i= 50 + (numThreads*stepSize);i<=1000;i++){
			plotValues[i-50].push_back(CorrelatedEntropy(windowSize,i));
		}
		for(int i=0;i<numThreads;i++){
			pthread_join(thread[i],NULL);
		}
		/*END THREAD MAGIC HERE*/

		
	}
	
	f.close();	
}

void Cem::write(){
	fstream g(dest.string(),std::ios::out);
	for(auto it = plotValues.begin();it!=plotValues.end();it++){
		for(auto it2 = (*it).begin();it2!=(*it).end();it2++)
			g<<*it2<<" ";
		g<<"\n";
	}
}
#endif