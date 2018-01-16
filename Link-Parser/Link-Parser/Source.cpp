#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int main()
{
	ifstream read;
	read.open("Links.csv");

	vector<string> data;
	string dataString;
	string tempStr;

	vector <string> outputData;

	read >> dataString;
	read.close();

	stringstream sstream;

	sstream << dataString;

	while (getline(sstream, tempStr, ','))
	{
		data.push_back(tempStr);
	}

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i].find("mtgo-standings") != data[i].npos)
		{
			outputData.push_back("https://magic.wizards.com"+data[i]);
		} 

	}

	ofstream write;
	write.open("ListofWebsites.csv");
	

	for (int i = 0; i < outputData.size(); i++)
	{
		if (i < outputData.size() - 1)
			write << outputData[i] << ',';
		else
			write << outputData[i];
	}

}