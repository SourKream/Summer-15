#include "newCem.hpp"
#include <fstream>
#include <regex>
using namespace std;
using namespace boost::filesystem;
path destRoot;
path srcRoot;
vector<string> filenames;
struct attr2{
	int low;
	int high;
};
void* threadFunction2(void* attribute){
	attr2* tmp = (attr2*) attribute;
	for(int i = tmp->low;i<tmp->high;i++){
		string src =  srcRoot.string() + "/"+filenames[i];
		string dest = destRoot.string() + "/Data_"+filenames[i];
		Cem a(src,dest);
		a.operate(50000);
		a.write();
	}
}
int main(){
	string mroot;
	cout<<"Enter root: ";
	cin>>mroot;
	path root(mroot);
	srcRoot = root;
	path mList = root / "ListOfGenomes.txt";
	fstream f;
	
	f.open(mList.string());
	while(!f.eof()){
		string line;
		f>>line;
		if(regex_match(line,regex("NC.*")))
			filenames.push_back(line);
	}
	f.close();

	destRoot = root / "data";

	int numThreads = 4;
	int stepSize = filenames.size() / numThreads;
	pthread_t * thread = new pthread_t[numThreads];
	attr2* attributes = new attr2[numThreads];
	for(int i=0;i<numThreads;i++){
		attributes[i].low = i*stepSize;
		attributes[i].high = (i+1)*stepSize;
		pthread_create(&thread[i],NULL,&threadFunction2,&attributes[i]);
	}
	for(int i = stepSize* numThreads; i< filenames.size();i++){
		string src =  srcRoot.string() + "/"+filenames[i];
		string dest = destRoot.string() + "/Data_"+filenames[i];
		Cem a(src,dest);
		a.operate(50000);
		a.write();
	}
	for(int i=0;i<numThreads;i++){
		pthread_join(thread[i],NULL);
	}
	return 0;
}