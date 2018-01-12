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

	read >> dataString;
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
			cout << data[i] << endl;
			//data[i].erase();
		//	i--;
		}
	}


//	for (int i = 0; i < data.size(); i++)
//		cout << data[i] << endl;


	system("pause");
}