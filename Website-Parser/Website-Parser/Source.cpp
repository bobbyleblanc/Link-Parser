#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void CreatePlayerList(vector <string> & data, vector<string> & playerList)
{
	ifstream read;
	read.open("data.txt");

	string playersUnparsed;
	string tempString;

	while (getline(read, tempString))
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
			playerList.erase(playerList.begin() + i);
		}
	}
	for (int i = 0; i < playerList.size(); i++)			// Remove standings number
	{
		if (i < 9)
			playerList[i].erase(playerList[i].begin(), playerList[i].begin() + 1);
		else if (i<100)
			playerList[i].erase(playerList[i].begin(), playerList[i].begin() + 2);
	}

	for (int i = 0; i < playerList.size(); i++)			// Remove breakers
	{
		for (int j = 0; j < playerList[i].size(); j++)
		{
			if ((playerList[i][j] == '.') && (playerList[i][j - 1] == '0'))
			{
				playerList[i].erase(playerList[i].begin() + j - 1, playerList[i].end());
			}
		}
	}

	string playerPoints = "24";


	for (int i = 0; i < playerList.size(); i++)			// Remove match points from usernames
	{
		bool found = false;
		string tempPoints1{ playerList[i][playerList[i].size() - 1] };
		string tempPoints2{ playerList[i][playerList[i].size() - 2],playerList[i][playerList[i].size() - 1] };

		while (!found)
		{
			if (isdigit(tempPoints2[0]) && (tempPoints2 == playerPoints) && (stoi(playerPoints)>9))
			{
				playerList[i].erase(playerList[i].begin() + playerList[i].size() - 2, playerList[i].end());
				found = true;
			}
			else if (tempPoints1 == playerPoints)
			{

				playerList[i].erase(playerList[i].begin() + playerList[i].size() - 1, playerList[i].end());
				found = true;
			}
			else
			{
				playerPoints = to_string(stoi(playerPoints) - 3);
			}
		}
	}



}
void CreateDecklists(vector <string> & data, vector<string> & playerList, vector <vector<string>> & deckLists)
{

	for (int i = 0; i < playerList.size(); i++)
	{
		int startPos;
		int startDecklistPos;
		vector <string> tempDecklist;
		tempDecklist.push_back(playerList[i]);

		for (int j = 0; j<data.size(); j++)						// Use player name to locate where to extract decklist
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
				startDecklistPos = j + 1;
				break;
			}
		}

		bool foundDeckEnd = false;
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



}
void OutputDecklists(vector <vector<string>> & decklists, string filename)
{
	ofstream writeDecklists(filename);		// Create decklist output to save

	for (int i = 0; i < decklists.size(); i++)
	{
		writeDecklists << decklists[i][0] << "'s Deck :" << endl;
		for (int j = 1; j < decklists[i].size(); j++)
			writeDecklists << decklists[i][j] << endl;

		writeDecklists << endl;
	}
}
void ReadLeagueData(vector <string> & data, string inputFilename)
{
	ifstream read;
	
	read.open(inputFilename);
	string tempString;

	while (getline(read, tempString))
	{
		if (tempString.empty())
		{

		}
		else
			data.push_back(tempString);
	}

	read.close();

}
void CreateLeagueDecklists(vector <string> & data, vector <vector<string>> & decklists)
{
	bool done = false;
	int startDecklistPos = 0;
	while(!done)
	{
		vector <string> tempDecklist;
		bool first_element = true;
		for (int j = startDecklistPos; j < data.size(); j++)
		{
			if (data[j].find("OverviewColorCostRarity") != data[j].npos) // Find where decklist begins
			{
				startDecklistPos = j + 1;
				break;
			}
			else if (j == data.size() - 1)
			{
				done = true;
			}
		}
	if (done)
	break;
		bool foundDeckEnd = false;
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
				if (first_element)
				{
					tempDecklist.push_back(data[startDecklistPos - 6]);
					first_element = false;
				}
				tempDecklist.push_back(data[startDecklistPos]);		// Add decklist element to tempDecklist
				startDecklistPos++;
			}

		}
		decklists.push_back(tempDecklist);			// Add completed decklist to vector
	}

}
int main()
{

	vector<string> data;
	vector <string> playerList;
	vector <vector<string>> decklists;

	vector<string> vintageData;
	vector <vector<string>> vintageDecklists;
	vector<string> commanderData;
	vector <vector<string>> commanderDecklists;
	vector<string> legacyData;
	vector <vector<string>> legacyDecklists;
	vector<string> pauperData;
	vector <vector<string>> pauperDecklists;
	vector<string> modernData;
	vector <vector<string>> modernDecklists;
	vector<string> standardData;
	vector <vector<string>> standardDecklists;

	vector<string> outputFilenames;
	vector<string> inputFilenames;

	inputFilenames.push_back("VintageOutput.txt");
	outputFilenames.push_back("VintageDecklists.csv");
	inputFilenames.push_back("CommanderOutput.txt");
	outputFilenames.push_back("CommanderDecklists.csv");
	inputFilenames.push_back("LegacyOutput.txt");
	outputFilenames.push_back("LegacyDecklists.csv");
	inputFilenames.push_back("PauperOutput.txt");
	outputFilenames.push_back("PauperDecklists.csv");
	inputFilenames.push_back("ModernOutput.txt");
	outputFilenames.push_back("ModernDecklists.csv");
	inputFilenames.push_back("StandardOutput.txt");
	outputFilenames.push_back("StandardDecklists.csv");


	outputFilenames.push_back("Decklists.csv");

	CreatePlayerList(data, playerList);				// For challenges
	CreateDecklists(data, playerList, decklists);	// For challenges
	OutputDecklists(decklists, outputFilenames[0]);	// For challenges
	
	ReadLeagueData(vintageData, inputFilenames[0]);
	ReadLeagueData(commanderData, inputFilenames[1]);
	ReadLeagueData(legacyData, inputFilenames[2]);
	ReadLeagueData(pauperData, inputFilenames[3]);
	ReadLeagueData(modernData, inputFilenames[4]);
	ReadLeagueData(standardData, inputFilenames[5]);

	CreateLeagueDecklists(vintageData, vintageDecklists);
	CreateLeagueDecklists(commanderData, commanderDecklists);
	CreateLeagueDecklists(legacyData, legacyDecklists);
	CreateLeagueDecklists(pauperData, pauperDecklists);
	CreateLeagueDecklists(modernData, modernDecklists);
	CreateLeagueDecklists(standardData, standardDecklists);

	OutputDecklists(vintageDecklists, outputFilenames[0]);
	OutputDecklists(commanderDecklists, outputFilenames[1]);
	OutputDecklists(legacyDecklists, outputFilenames[2]);
	OutputDecklists(pauperDecklists, outputFilenames[3]);
	OutputDecklists(modernDecklists, outputFilenames[4]);
	OutputDecklists(standardDecklists, outputFilenames[5]);


	system("pause");
}