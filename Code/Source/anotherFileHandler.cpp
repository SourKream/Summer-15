#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <regex>
using namespace std;
using namespace boost::filesystem;

int main(int argc, char* argv[]){
	if(argc!=2){
		cout<<"ERROR: SYNTAX: ./folderStructure.out <FOLDER_NAME>\n";
		return 1;
	}
	path root(argv[1]);
	directory_iterator it(root),eod;
	BOOST_FOREACH(path const& p,make_pair(it,eod)){
		if(is_directory(p)){
			BOOST_FOREACH(path const& q,make_pair(p,eod)){
				if(is_regular_file(q)){
					path dest = it / q.filename().string();
					copy_file(q,dest);
				}
			}
		}
	}
return 0;
}