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
		else if (tempString.empty())
		{

		}
		else
			data.push_back(tempString);
	}

	read.close();
	
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
		if (i < 9)
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
	
	
	for (int i = 0; i < playerList.size(); i++)			// Remove match points from usernames
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
	

	vector <vector<string>> deckLists;

	
	for (int i = 0; i < playerList.size(); i++)
	{
		int startPos;
		int startDecklistPos;
		vector <string> tempDecklist;
		tempDecklist.push_back(playerList[i]);

		for(int j=0; j<data.size(); j++)						// Use player name to locate where to extract decklist
		{	
			if (data[j].find(playerList[i]) != data[j].npos)
			{
				startPos = j;
				break;
			}
		}
		
		for (int j = startPos; j < data.size(); j++)
		{
			if (data[j].find("OverviewColorCostRarity") != data[j].npos) // Find where decklist begins
			{
				startDecklistPos = j+1;
				break;
			}
		}

		int foundDeckEnd = false;
		while (!foundDeckEnd)					// Find where decklist ends
		{
			if (data[startDecklistPos].find("Blue (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("White (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Red (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Black (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Green (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else
			{
				tempDecklist.push_back(data[startDecklistPos]);		// Add decklist element to tempDecklist
				startDecklistPos++;
			}

		}
		deckLists.push_back(tempDecklist);			// Add completed decklist to vector
	}
	
	
	ofstream writeDecklists("Decklists.csv");		// Create decklist output to save

	for (int i = 0; i < deckLists.size(); i++)
	{
		writeDecklists << deckLists[i][0] << "'s Deck :" << endl;
		for (int j = 1; j < deckLists[i].size(); j++)
			writeDecklists << deckLists[i][j] << endl;

		writeDecklists << endl;
	}

	

	system("pause");
}