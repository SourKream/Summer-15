#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <regex>
using namespace std;
using namespace boost::filesystem;

int numFiles(path& p){
	directory_iterator it(p),eod;
	int count=0;
	BOOST_FOREACH(path const&p,make_pair(it,eod)){
		if(is_regular_file(p)){
			string filename = p.filename().string();
			if(regex_match(filename,regex("AC_NC_.*"))){
				count++;
			}
		}
	}
	return count;
}

int main(){
	path root("Genome/");
	directory_iterator it(root),eod;
	BOOST_FOREACH(path const& p, make_pair(it,eod)){
		string fname = p.filename().string();
		if(regex_match(fname,regex("NC_00.*"))){	
			path tmp = root / fname / "AutoCorrelate/";
			int x = numFiles(tmp);
			if(x!=951){
				std::cout<<fname<<"\t"<<x<<"\n";
			}
		}
	}
	return 0;
}
