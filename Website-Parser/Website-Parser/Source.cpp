#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

inline bool isInteger(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}
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
		bool foundSB = false;
		writeDecklists << decklists[i][0] << "'s Deck :" << endl;
		for (int j = 2; j < decklists[i].size(); j++)
		{
			if (j % 2 == 0)
				writeDecklists << '"' << decklists[i][j] << '"' << ",";
			else
				writeDecklists << '"' << decklists[i][j] << '"' << endl;		
		}
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
			else if (data[j].find("generalColorCosteRareza") != data[j].npos) // Find where decklist begins
			{
				startDecklistPos = j + 1;
				break;
			}
			else if (data[j].find("PanoramicaColoreCosto") != data[j].npos) // Find where decklist begins
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
			else if (data[startDecklistPos].find("Azul (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Blu (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("White (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Blanco (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Bianco (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Red (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Rosso (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Black (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Negro (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Nero (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Green (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Verde (") != data[startDecklistPos].npos)
			{
				foundDeckEnd = true;
				break;
			}
			else if (data[startDecklistPos].find("Creature (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Criatura (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Creatura (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if ((data[startDecklistPos].find("Tribal") != data[startDecklistPos].npos) && (data[startDecklistPos].find("(") != data[startDecklistPos].npos))
			{
				startDecklistPos++;
			}
			else if ((data[startDecklistPos].find("Legendary") != data[startDecklistPos].npos) && (data[startDecklistPos].find("(") != data[startDecklistPos].npos))
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Instant (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if ((data[startDecklistPos].find("Instant") != data[startDecklistPos].npos) && (data[startDecklistPos].find("(") != data[startDecklistPos].npos))
			{
				startDecklistPos++;
			}
			else if ((data[startDecklistPos].find("Istantaneo") != data[startDecklistPos].npos) && (data[startDecklistPos].find("(") != data[startDecklistPos].npos))
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Sorcery (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Stregoneria (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Conjuro (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Land (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Tierra (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Terra (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Artifact (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Artefacto (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Artefatto (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Enchantment (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Encantamiento (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Incantesimo (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else if (data[startDecklistPos].find("Planeswalker (") != data[startDecklistPos].npos)
			{
				startDecklistPos++;
			}
			else
			{
				if (first_element)
				{
					tempDecklist.push_back(data[startDecklistPos - 7].substr(0, data[startDecklistPos - 7].size() - 6));
				//	tempDecklist.push_back(data[startDecklistPos - 7]);
					first_element = false;
				}
				tempDecklist.push_back(data[startDecklistPos]);		// Add decklist element to tempDecklist
				startDecklistPos++;
			}

		}
		decklists.push_back(tempDecklist);			// Add completed decklist to vector
	}

}
void FixOrderIfBroken(vector <vector<string>> & decklists)
{
	for (int i = 0; i < decklists.size(); i++)
	{
		for (int j = 0; j < decklists[i].size(); j++)
		{
			if ((j % 2 == 1)&&(isInteger(decklists[i][j])))
			{
				decklists[i].insert(decklists[i].begin() + j, " ");
			}
		}
	}
}
int main()
{
	ifstream getDate;
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
	
	string date;
	getDate.open("date.txt");
	getDate >> date;
	
	inputFilenames.push_back(date + "/VintageOutput.txt");
	outputFilenames.push_back(date + "/VintageDecklists.csv");
	inputFilenames.push_back(date + "/CommanderOutput.txt");
	outputFilenames.push_back(date + "/CommanderDecklists.csv");
	inputFilenames.push_back(date + "/LegacyOutput.txt");
	outputFilenames.push_back(date + "/LegacyDecklists.csv");
	inputFilenames.push_back(date + "/PauperOutput.txt");
	outputFilenames.push_back(date + "/PauperDecklists.csv");
	inputFilenames.push_back(date + "/ModernOutput.txt");
	outputFilenames.push_back(date + "/ModernDecklists.csv");
	inputFilenames.push_back(date + "/StandardOutput.txt");
	outputFilenames.push_back(date + "/StandardDecklists.csv");
	outputFilenames.push_back("Decklists.csv");

	//	CreatePlayerList(data, playerList);				// For challenges
	//	CreateDecklists(data, playerList, decklists);	// For challenges
	//	OutputDecklists(decklists, outputFilenames[0]);	// For challenges
	
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

	FixOrderIfBroken(vintageDecklists);
	FixOrderIfBroken(commanderDecklists);
	FixOrderIfBroken(legacyDecklists);
	FixOrderIfBroken(pauperDecklists);
	FixOrderIfBroken(modernDecklists);
	FixOrderIfBroken(standardDecklists);

//	for (int i = 0; i < standardDecklists.size(); i++)
//	{
//		for (int j = 0; j < standardDecklists[i].size(); j++)
//			cout << standardDecklists[i][j] << endl;
//		
//		cout << endl;
//	}
//	system("pause");
	OutputDecklists(vintageDecklists, outputFilenames[0]);
	OutputDecklists(commanderDecklists, outputFilenames[1]);
	OutputDecklists(legacyDecklists, outputFilenames[2]);
	OutputDecklists(pauperDecklists, outputFilenames[3]);
	OutputDecklists(modernDecklists, outputFilenames[4]);
	OutputDecklists(standardDecklists, outputFilenames[5]);

}