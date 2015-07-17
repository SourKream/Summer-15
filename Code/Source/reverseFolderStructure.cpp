// To remove all Autocorrelate Crosscorrelate and GCSkew folders

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <regex>
using namespace std;
using namespace boost::filesystem;

int main(){
	/*if(argc!=2){
		cout<<"ERROR: SYNTAX: ./folderStructure.out <FOLDER_NAME>\n";
		return 1;
	}*/
	string fname;
	cout<<"Enter folder name \n";
	cin>>fname;
	path root(fname);
	directory_iterator it(root),eod;
	int count=0;
	BOOST_FOREACH(path const& p, make_pair(it,eod)){
		if(is_directory(p)){
			string folder_name = p.filename().string();
			if(regex_match(folder_name,regex("NC_.*"))){
				
				path genome_folder = root / folder_name;
				path autoCorrelate = genome_folder/"AutoCorrelate";
				path crossCorrelate = genome_folder/"CrossCorrelate";
				path gcskew = genome_folder/"GCSkew";
				remove_all(autoCorrelate);
				remove_all(crossCorrelate);
				remove_all(gcskew);

				count++;
			}
			
		}
	}
	cout<<"Number of genomes cleared:"<<count<<"\n";
	return 0;
}