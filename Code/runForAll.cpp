#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	int NumberOfFiles = 0;

	fstream fil;
	fil.open("Genome/GenomeList.txt",ios::in);

	string filename;
	char line[100];

	while(fil.getline(line,100))
	{
		filename = line;
		filename = filename.substr(0,filename.find_last_of('.'));

		cout << "PROCESSING " << filename << endl << endl;

		for (int i=50; i<1000; i++)
		{
			string command = "make execute FNAME='Genome/" + filename + "/" + filename + ".txt' SUBWINSIZE=" + to_string(i);
			cout << command << endl;
			system(command.c_str());
		}

		NumberOfFiles++;
		cout << endl << NumberOfFiles << " GENOMES PROCESSED\n\n";
	}
	fil.close();
}
