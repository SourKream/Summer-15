#include <iostream>
#include <fstream>
#include <vector>
#include <pthread.h>
using namespace std;
vector<string> filenames;
struct attr{
	int low;
	int high;
	string* fname;
};

int NumberOfFiles = 0;
void *threadSubFunction(void* attribute){
	attr* tmp = (attr*) attribute;
	string filename = *(tmp->fname);
	for(int i = tmp->low;i<tmp->high;i++){
		string command = "make execute FNAME='Genome/" + filename + "/" + filename + ".txt' SUBWINSIZE=" + to_string(i);
		system(command.c_str());
	}
}
void *threadFunction(void* attribute){
	attr* tmp = (attr*) attribute;
	for(int i = tmp->low;i<tmp->high;i++){
		string filename = filenames[i];
		int numThreads = 50;
		pthread_t * thread = new pthread_t[numThreads];
		attr* attributes = new attr[numThreads];
		int stepSize = 951 / numThreads;

		for (int j=0;j<numThreads;j++){
			attributes[j].low = 50 + (j*stepSize);
			attributes[j].high = 50 + ((j+1)*stepSize);
			attributes[j].fname = & filename;
			pthread_create(&thread[j],NULL,&threadSubFunction,&attributes[j]);
		}
		for(int j= 50 + (numThreads*stepSize);j<=1000;j++){
			string command = "make execute FNAME='Genome/" + filename + "/" + filename + ".txt' SUBWINSIZE=" + to_string(j);
			system(command.c_str());
		}
		for (int j=0;j<numThreads;j++){
			pthread_join(thread[j],NULL);
		}
	}
	NumberOfFiles++;
	//std::cout<<NumberOfFiles<<" PROCESSED \n\n";
}
int main()
{
	
	
	fstream fil;
	fil.open("Genome/GenomeList.txt",ios::in);

	string filename;
	char line[100];
	int count = 0;
	while(fil.getline(line,100)){
		filename = line;
		filename = filename.substr(0,filename.find_last_of('.'));
		if(filename=="NC_008321")
			count=1;
		if(count==1)
			filenames.push_back(filename);
	}
	fil.close();

	int numThreads = 4;
	pthread_t* thread = new pthread_t[numThreads];
	attr* attributes = new attr[numThreads];
	int numFiles = filenames.size();

	int stepSize = numFiles / numThreads;
	for(int i=0;i<numThreads;i++){
		attributes[i].low = i * stepSize;
		attributes[i].high = (i+1) * stepSize;
		pthread_create(&thread[i],NULL,&threadFunction,&attributes[i]);
	}
	for(int i=numThreads*stepSize;i<numFiles;i++){
		string filename = filenames[i];
		//std::cout<<"PROCESSING"<< filename <<"\n\n";

		for (int j=50;j<=1000;j++){
			string command = "make execute FNAME='Genome/" + filename + "/" + filename + ".txt' SUBWINSIZE=" + to_string(j);
			//cout << command << "\n";
			system(command.c_str());
		}
	}
	for(int i=0;i<numThreads;i++){
		pthread_join(thread[i],NULL);
	}
	return 0;
}
