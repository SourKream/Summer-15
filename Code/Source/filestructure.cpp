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
	name.erase(name.find(".txt"),4);
	path root("");
	path folderName = root/name;
	
	if(!exists(folderName) || !is_directory(folderName)){
		create_directory(folderName);
	}
	root=folderName;
	path autoCorrelate = root/"auto";
	path crossCorrelate = root/"cross";
	path gcskew = root/"gcskew";
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