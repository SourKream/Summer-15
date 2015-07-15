#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <regex>
using namespace std;
using namespace boost::filesystem;

struct data{
	int aContent;
	int tContent;
	int gContent;
	int cContent;
	string name;
	int length;
	void reset(){
		aContent=tContent=gContent=cContent=length=0;
	}
};

void mFunc(data& tmp,string filname){
	fstream f(filname);
	tmp.reset();
	string line; 
	getline(f,line,'\n');
	while(!f.eof()){
		char letter = f.get();
		switch(letter){
			case 'A': tmp.aContent++;tmp.length++;break;
			case 'T': tmp.tContent++;tmp.length++;break;
			case 'G': tmp.gContent++;tmp.length++;break;
			case 'C': tmp.cContent++;tmp.length++;break;
			default:break;
		} 
	}
	f.close();
}
int main(){
	string rootDir;
	std::cout<<"Enter root directory: ";
	cin>>rootDir;
	path root(rootDir);
	fstream destFile;
	destFile.open("AllData.txt",ios::out);
	directory_iterator it(root),eod;
	data x;
	BOOST_FOREACH(const path& p, make_pair(it,eod)){
		if(regex_match(p.filename().string(),regex("NC.*"))){
			directory_iterator mIt(p);
			BOOST_FOREACH(const path& q,make_pair(mIt,eod)){
				if(is_regular_file(q) && regex_match(q.filename().string(),regex("NC.*"))){
					mFunc(x,q.string());
					destFile<<q.filename().string()<<" "<<x.length<<" "<<x.aContent<<" "<<x.tContent<<" "<<x.gContent<<" "<<x.cContent<<"\n";
				}
			}
		}
	}
	return 0;
}