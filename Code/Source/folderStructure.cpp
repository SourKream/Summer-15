#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <regex>
using namespace std;
using namespace boost::filesystem;

int main(int argc,char* argv[]){
	if(argc!=2){
		cout<<"ERROR: SYNTAX: ./folderStructure.out <FOLDER_NAME>\n";
		return 1;
	}
	path root(argv[1]);
	directory_iterator it(root),eod;
	int count=0;
	BOOST_FOREACH(path const& p, make_pair(it,eod)){
		if(is_regular_file(p)){
			string file_name = p.filename().string();
			if(regex_match(file_name,regex("NC_.*"))){
				string temp = file_name;
				string folder_name = file_name.erase(file_name.find(".txt"),string::npos);
				path src_file = root / temp;
				path dest_folder = root / folder_name;
				path dest_file = dest_folder / temp;
				if(!exists(dest_folder) || !is_directory(dest_folder)){
					create_directory(dest_folder);
				}
				copy_file(src_file,dest_file);
				remove_all(src_file);
				path autoCorrelate = dest_folder/"AutoCorrelate";
				path crossCorrelate = dest_folder/"CrossCorrelate";
				path gcskew = dest_folder/"GCSkew";
				if(!exists(autoCorrelate) || !is_directory(autoCorrelate)){
					create_directory(autoCorrelate);
				}
				if(!exists(crossCorrelate) || !is_directory(crossCorrelate)){
					create_directory(crossCorrelate);
				}
				if(!exists(gcskew) || !is_directory(gcskew)){
					create_directory(gcskew);
				}
				count++;
			}
			
		}
	}
	cout<<"Number of folders made:"<<count<<"\n";
	return 0;
}