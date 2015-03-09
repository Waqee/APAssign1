#include "Team.h"
#include <fstream>
#include <string>

//Loads data from team.csv
Team::Team()
{
	ifstream file;
	file.open("../data/teams.csv");

	string idstring;
	string name;

	string temp;
	getline(file, temp);

	while (file.good())
	{

		getline(file, idstring, ',');
		getline(file, name);

		if (idstring == "")
			continue;
		int id = stoi(idstring);

		teams[id] = name;
	}
	file.close();
}

//Returns name of team
string Team::GetTeam(int id)
{
	return teams[id];
}

//Returns ID of team
int Team::GetTeamID(string name)
{
	for (auto it = teams.begin(); it != teams.end(); ++it)
	if (it->second.compare(name) == 0)
		return it->first;
}

//Returns all teams in a vector
vector<int> Team::GetAllTeams()
{
	vector<int> all_teams;
	for (auto it = teams.begin(); it != teams.end(); ++it)
		all_teams.push_back(it->first);

	return all_teams;
}