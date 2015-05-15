#ifndef CEM_CPP
#define CEM_CPP
#include "cem.hpp"

Cem::cem(int winSize,int subwinSize)
{
	windowSize = winSize;
	subWindowSize = subwinSize;
	numSubWindows = windowSize / subWindowSize;
	if (windowSize % subWindowSize)
		numSubWindows++;
}

Cem::cem()
{

}

void Cem::setWinSubWin(int winSize,int subWinSize)
{
	windowSize = winSize;
	subWindowSize = subWinSize;
	numSubWindows = windowSize / subWindowSize;
	if (windowSize % subWindowSize)
		numSubWindows++;
}

float Cem::Entorpy (int subWindowStartIndex)
{
	int subwindowLength = min(subWindowSize,((int)currWindow.length() - subWindowStartIndex));
	int freqA = 0, freqT = 0, freqC = 0, freqG = 0;
	
	for(int i=0; i<subwindowLength; i++)		// count number of times each base is present in the subwindow
		switch (subwindow[i + subWindowStartIndex])
	{
		case 'A':
			freqA++;
			break;
		case 'T':
			freqT++;
			break;
		case 'C':
			freqC++;
			break;
		case 'G':
			freqG++;
			break;
		default:
			break;
	}
	
	float probA = ((float)freqA/subwindowLength);	// probability of occurence of each base
	float probT = ((float)freqT/subwindowLength);
	float probC = ((float)freqC/subwindowLength);
	float probG = ((float)freqG/subwindowLength);
	
	float entropy = 0;
	
	if (!probA)						// in case any prob is 0, p*log(p) should go to 0, so p is set to 1 so that log(p) is 0
		probA = 1;
	if (!probT)
		probT = 1;
	if (!probC)
		probC = 1;
	if (!probG)
		probG = 1;
	
	entropy += probA * log2 (probA);	// As per the entropy formula
	entropy += probT * log2 (probT);
	entropy += probC * log2 (probC);
	entropy += probG * log2 (probG);
	entropy = -entropy;
	
	return entropy;
}

float Cem::CorrelatedEntropy()
{
	long windowLength = currWindow.length();				// The last window maybe smaller than the windowSize chosen
	float *entropySequence = new float[numSubWindows];			// Array to store the sequence of entropy values of each subwindow

	for(int i=0;i<numSubWindows;i++)
		entropySequence[i] = 0;
	
	int i;
	for (i=0; i*subWindowSize<windowLength; i++)
	{
		entropySequence[i] = Entropy(i*subWindowSize);						// and its entropy value stored in array
	}
	
	return AutoCorrelate(entropySequence, i);		// Autocorrealtion is applied on the array
													// and the resulting correlated entropy measure of the
													// window is returned
}

float Correlate (int k, float seq[], int N, float &mean, float &variance) // Subfunction of autocorrelation function
{
	float Ck = 0;
	for (int i=0; i<N-k; i++)
		Ck += (seq[i] - mean)*(seq[i+k] - mean);
	
	Ck /= (N-k);
	Ck /= (variance);
	return Ck;
}

float Cem::AutoCorrelate (float seq[], int N) // Standard Autocorrelation function
{
	float seqMean =0, seqVariance =0;
	
	for (int i=0; i<N; i++)		// To find the mean of the sequence
		seqMean += seq[i];
	seqMean /= N;
	
	for (int i=0; i<N; i++)											// To find the variance of the sequence
		seqVariance += (seq[i] - seqMean)*(seq[i] - seqMean);
	seqVariance /= N;
	
	float C = 0;
	
	for (int i=1; i<N; i++)
		C += fabs(Correlate(i, seq, N, seqMean, seqVariance));
	
	C /= (N-1);
	
	return C;
}

#endif