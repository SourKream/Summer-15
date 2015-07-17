// Removes the first few lines of comments added by Octave from the data files.

#include <iostream>
#include <fstream>
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
				string file_name = "AC_" + folder_name + "_50000.txt";

				ifstream fil1((root / folder_name / file_name).c_str());
				ofstream fil2((root / folder_name / "out.txt").c_str());

				char lin[1000000];
				while(fil1.getline(lin,1000000))
				{
					if (lin[0]!='#')
						fil2 << lin << endl;
				}  

				fil1.close();
				fil2.close();

				rename(root / folder_name / "out.txt", root / folder_name / file_name);

				count++;
			}
			
		}
	}
	cout<<"Number of files touched:"<<count<<"\n";
	return 0;
}