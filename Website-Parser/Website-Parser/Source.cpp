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
			if ((playerList[i][j] == '.')&&(playerList[i][j-1]=='0'))
			{
				playerList[i].erase(playerList[i].begin() + j - 1, playerList[i].end());
			}
		}
	}

	string playerPoints = "24";
	
	
	for (int i = 0; i < playerList.size(); i++)
	{
		bool found = false;
		string tempPoints1{playerList[i][playerList[i].size()-1]};
		string tempPoints2{playerList[i][playerList[i].size() - 2],playerList[i][playerList[i].size() - 1] };
		
		while (!found)
		{
			if (isdigit(tempPoints2[0])&&(tempPoints2 == playerPoints)&&(stoi(playerPoints)>9))
			{
				playerList[i].erase(playerList[i].begin() + playerList[i].size() - 2, playerList[i].end());
				found = true;
			}
			else if (tempPoints1 == playerPoints)
			{
				
				playerList[i].erase(playerList[i].begin() + playerList[i].size()-1, playerList[i].end());
				found = true;
			}
			else
			{
				playerPoints = to_string(stoi(playerPoints) - 3);
			}
		}
	}
	
	
	for (int i = 0; i < playerList.size(); i++)
		cout << playerList[i] << endl;

	vector <string> deckLists;

	

	

	system("pause");
}