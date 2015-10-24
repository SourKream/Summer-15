#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <ctype.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <regex>
using namespace std;
using namespace boost::filesystem;

/*

Finds the Gene Count .ie. frequency of occurance of every 'N' base long 
sequence possible in the Genome.

To run compile with g++ GeneSignature.cpp -lboost_system -lboost_filesystem

The generated a.out file must be placed in the Genome Folder before running.

Output placed in GeneSignature.txt file.

*/


const int N = 8;
const long NumOfSeq = 131072;	// Remember to set NumOfSeq = 4^N

void GeneCount (string src, int count[])
{
	std::fstream f;
	f.open(src,ios::in);
	string notNeeded;
	getline(f,notNeeded);
	for (int i=0; i<NumOfSeq; i++)
		count[i] = 0;

	char ch;
	int hash = 0;
	for (int i=0; i<N; i++)
	{	
		ch = f.get();
		if(isalpha(ch))
		{
			hash *= 4;
			switch (ch)
			{
				case 'T' : hash += 1;
				break;
				case 'C' : hash += 2;
				break;
				case 'G' : hash += 3;
			}
		}
		else
			i--;
	}

	count[hash]++;

	while(!f.eof())
	{
		ch = f.get();
		if (isalpha(ch))
		{
			hash *= 4;
			switch (ch)
			{
				case 'T' : hash += 1;
				break;
				case 'C' : hash += 2;
				break;
				case 'G' : hash += 3;
			}
			hash %= NumOfSeq;
			count[hash]++;
		}
	}
	
	f.close();
}

int main()
{
	fstream fout;
	fout.open("GeneSignature.txt",ios::out);
	string fname = "GenomeName";
	path root(fname);
	directory_iterator it(root),eod;
	int count[NumOfSeq] = {};
	int c = 0;
	BOOST_FOREACH(path const& p, make_pair(it,eod))
	{
		if(is_regular_file(p))
		{
			string file_name = p.filename().string();
			if(regex_match(file_name,regex("NC_.*")))
			{
				GeneCount(p.string(), count);
				for (int i=0; i<NumOfSeq; i++)
					fout << count[i] << " ";
				fout << endl;
				c++;
				cout<<"Number of Genomes analysed: "<<c<<"\r";
				fflush(stdout);
			}
		}
	}

	fout.close();
}
