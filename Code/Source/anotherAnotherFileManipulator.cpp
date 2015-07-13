#include <iostream>
#include <string>
#include <unordered_set>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <regex>
using namespace std;
using namespace boost::filesystem;

int main(){
	string listOfFileNames;
	unordered_set<string> dirOfFiles;
	cout<<"Enter list of files \n";
	cin>>listOfFileNames;
	fstream f;
	f.open(listOfFileNames,ios::in);
	while(!f.eof()){
		string tmp;
		f>>tmp;
		dirOfFiles.insert(tmp);
	}
	f.close();
	string root;
	cout<<"Enter the root directory \n";
	cin>>root;
	path mRoot(root);
	directory_iterator it(mRoot),eod;
	BOOST_FOREACH(const path &p,make_pair(it,eod)){
		if(is_regular_file(p)){
			if(regex_match(p.filename().string(),regex("NC.*"))){
				auto got = dirOfFiles.find(p.filename().string());
				if(got==dirOfFiles.end()){
					remove_all(p);
				}
			}
		}
	}
	return 0;
}