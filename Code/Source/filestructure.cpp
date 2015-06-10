#include <iostream>
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost::filesystem;

int main(int argc,char* argv[]){
	path root("Genome");
	path folderName = root/argv[1];
	
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