#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;

int main(int argc,char* argv[]){
	string name=argv[1];
	if(name==""){
		cout<<"SYNTAX: ./filestructure.out <FILENAME>\n";
		return 1;
	}
	path root(name);
	path folderName = root.parent_path();
	
	if(!exists(folderName) || !is_directory(folderName)){
		create_directory(folderName);
	}
	root=folderName;
	path autoCorrelate = root/"AutoCorrelate";
	path crossCorrelate = root/"CrossCorrelate";
	path gcskew = root/"GCSkew";
	if(!exists(autoCorrelate) || !is_directory(autoCorrelate)){
		create_directory(autoCorrelate);
	}
	if(!exists(crossCorrelate) || !is_directory(crossCorrelate)){
		create_directory(crossCorrelate);
	}
	if(!exists(gcskew) || !is_directory(gcskew)){
		create_directory(gcskew);
	}
return 0;

}