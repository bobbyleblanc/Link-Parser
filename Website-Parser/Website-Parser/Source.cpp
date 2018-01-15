#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	ifstream read;

	read.open("data.txt");

	vector<string> data;
	string playersUnparsed;
	string tempString;
	stringstream sstream;

	while (getline(read,tempString))
	{
		if (tempString.find("RankNamePointsOMWPGWPOGWP") != tempString.npos)
			playersUnparsed = tempString;
		else
			data.push_back(tempString);
	}

	read.close();
	ofstream write("dataOutput.txt");

	for (int i = 0; i < data.size(); i++)
	{
		write << data[i] << endl;
	}

	write.close();

	stringstream playerStrStream;
	playerStrStream << playersUnparsed;
	vector <string> playerList;

	bool skip_first = true;

	while (getline(playerStrStream, tempString, ' '))		// Populate player list
	{
		if (skip_first)
		{
			skip_first = false;
		}
		else
		{
			playerList.push_back(tempString);
		}
	}

	for (int i = 0; i < playerList.size(); i++)			// Fix players with space in username
	{
		if (!isdigit(playerList[i][0]))
		{
			playerList[i - 1] = playerList[i - 1] + " " + playerList[i];
			playerList.erase(playerList.begin()+i);
		}
	}
	for (int i = 0; i < playerList.size(); i++)			// Remove standings number
	{
		if (i < 10)
		 playerList[i].erase(playerList[i].begin(),playerList[i].begin()+1);
		else if(i<100) 
		 playerList[i].erase(playerList[i].begin(), playerList[i].begin() + 2);
	}

	for (int i = 0; i < playerList.size(); i++)			// Remove breakers
	{
		for (int j = 0; j < playerList[i].size(); j++)
		{
			if (playerList[i][j] == '.')
			{
				playerList[i].erase(playerList[i].begin() + j - 3, playerList[i].end());
			}
		}
	}

	

	vector <string> deckLists;

	

	

	system("pause");
}