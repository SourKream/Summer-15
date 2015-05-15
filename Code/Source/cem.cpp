#ifndef CEM_CPP
#define CEM_CPP
#include "cem.hpp"
Cem::cem(int winSize,int subwinSize){
	windowSize = winSize;
	subWindowSize = subwinSize;
}
Cem::cem(){

}

void Cem::setWinSubWin(int winSize,int subWinSize){
	windowSize = winSize;
	subWindowSize = subWinSize;
}


#endif