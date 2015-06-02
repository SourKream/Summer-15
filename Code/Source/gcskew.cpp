#ifndef GC_SKEW_CPP
#define GC_SKEW_CPP
 
#include "gcskew.hpp"
#define SHIFT_FRACTION 1
std::string GcSkew::getFileName(){
	return fileName;
}

GcSkew::GcSkew(int winSize){
	windowSize = winSize;
	shiftFraction = SHIFT_FRACTION;
	debug = false;
}

GcSkew::GcSkew(){
	shiftFraction = SHIFT_FRACTION;
	debug = false;
}

void GcSkew::setWindowSize(int winSize){
	windowSize = winSize;
}

float GcSkew::gcSkewEvaluate(){
	int G_Count = 0, C_Count=0;
	for(int i = 0;i<currWindow.length();++i){
	
		if(currWindow[i] == 'G' || currWindow[i] == 'g')
			G_Count++;
		else if(currWindow[i] == 'C' || currWindow[i] == 'c')
			C_Count++;
	}
	return float(C_Count - G_Count)/ float(C_Count + G_Count);
}

void GcSkew::operate(const std::string& src){

	std::fstream f;
	f.open(src,std::ios::in);
	float shiftMargin = 1.0 - shiftFraction;
	if(!f){
		std::cout<<"Error while opening file \n";
		return;
	}

	fileName = src.substr(src.find_last_of('/')+1);
	fileName = fileName.substr(0,fileName.find_last_of('.'));
	fileName += "_" + std::to_string(windowSize);

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
				if(parse%80==0)
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
		plotValues.push_back(gcSkewEvaluate());
		if(!f.eof()){
			
			f.seekg(-shiftMargin * windowSize * sizeof(char),std::ios::cur); // For overlapping windows.
		}

	}

	f.close();

}

void GcSkew::write(const std::string &dest){
	
	std::fstream filOut;
	filOut.open("Data/GenomeData.txt",std::ios::out);
	for(int i=0;i<plotValues.size();i++){
		filOut<<plotValues[i]<<"\n";
	}

	
}

void GcSkew::setDebugFlag(){
	debug = true;
}


#endif