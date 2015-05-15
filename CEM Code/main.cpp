//
//  main.cpp
//  CEM
//
//  Created by Shantanu Kumar on 14/05/15.
//  Copyright (c) 2015 Shantanu Kumar. All rights reserved.
//
//  Use 'plot "Output.txt" with lines, "Output.txt" with points'
//  with gnuplot on terminal to produce the plot
//

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

int windowSize;
int subWindowSize;
int numSubWindows;

float CorrelatedEntropy (string window);
float Entropy (string subwindow);
float AutoCorrelate (float [], int);

int main (int argc, char *argv[])
{
	if (argc != 3)
	{
		cout << "\nSyntax: ./CEM.o <Window_Size> <SubWindow_Size>\n\n";
		return 0;
	}

	windowSize = atof(argv[1]);
	subWindowSize = atof(argv[2]);
	numSubWindows = windowSize / subWindowSize;

	if (subWindowSize > windowSize)
	{
		cout << "\nInvalid Values for window size and subwindow size\n\n";
		return 0;
	}

	cout << "\nWindow Size: " << windowSize << endl;
	cout << "SubWindow Size: " << subWindowSize << endl;

	cout << "\nPerforming CEM...\n\n";

	fstream filIn, filOut;
	filIn.open("Genome.txt",ios::in);	//Text file containing only the genome
	filOut.open("Output.txt",ios::out);	//Text file containing CEM output
	int windowNumber = 0;

	while (!filIn.eof())
	{
		string window;
		char A;
		for (int i=0; (i<windowSize && !filIn.eof()); i++)			// Extract windowSize number of genome bases
		{
			A = filIn.get();
			if ((A == 'A')||(A == 'T')||(A == 'C')||(A == 'G'))
				window += A;											// A genome window is added to the window variable base by base
			else
				i--;
		}
		windowNumber++;
		filOut << windowNumber << " " << CorrelatedEntropy(window) << endl;				// Correlated Entropy of th window is caluculated
	}
	
	filOut.close();
	filIn.close();
	system("gnuplot plot.plt");

	char command[100] = "mv Plot.svg Plot_";
	strcat(command, argv[1]);
	strcat(command, "_");
	strcat(command, argv[2]);
	strcat(command, ".svg");
	system(command);
	cout << "Output Generated: \"Plot_" << argv[1] << "_" << argv[2] << ".svg\"\n\n";
	
	return 1;
}

float CorrelatedEntropy (string window)
{
	long windowLength = window.length();				// The last window maybe smaller than the windowSize chosen
	float *entropySequence = new float[numSubWindows];			// Array to store the sequence of entropy values of each subwindow

	for(int i=0;i<numSubWindows;i++)
		entropySequence[i] = 0;

	string subWindow;
	
	int i;
	for (i=0; i*subWindowSize<windowLength; i++)
	{
		subWindow = window.substr(i*subWindowSize,subWindowSize);		// A single subwindow is extracted
		entropySequence[i] = Entropy(subWindow);						// and its entropy value stored in array
	}
	
	return AutoCorrelate(entropySequence, i);		// Autocorrealtion is applied on the array
													// and the resulting correlated entropy measure of the
													// window is returned
}

float Entropy (string subwindow)
{
	int subwindowLength = (int)subwindow.length();
	int freqA = 0, freqT = 0, freqC = 0, freqG = 0;
	
	for(int i=0; i<subwindowLength; i++)		// count number of times each base is present in the subwindow
		switch (subwindow[i])
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

float Correlate (int k, float seq[], int N, float &mean, float &variance) // Subfunction of autocorrelation function
{
	float Ck = 0;
	for (int i=0; i<N-k; i++)
		Ck += (seq[i] - mean)*(seq[i+k] - mean);
	
	Ck /= (N-k);
	Ck /= (variance);
	return Ck;
}

float AutoCorrelate (float seq[], int N) // Standard Autocorrelation function
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

