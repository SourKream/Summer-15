// Collects all the NC_.* files from separate sub folders and places them together in the root filder.

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
			directory_iterator dir(p);
			BOOST_FOREACH(path const& q,make_pair(dir,eod)){
				if(is_regular_file(q)){
					if(regex_match(q.filename().string(),regex("NC_.*"))){
						path dest(root);
						dest /= q.filename().string();
						rename(q,dest);
					}
				}
			}
		}
	}
return 0;
}