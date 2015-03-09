#pragma once
#include <unordered_map>
#include <vector>

using namespace std;

//Class for storing teams names against there id
class Team
{
	unordered_map<int, string> teams;
public:
	Team();
	string GetTeam(int id);
	int GetTeamID(string name);
	vector<int> GetAllTeams();
};