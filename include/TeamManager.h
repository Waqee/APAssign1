#pragma once
#include "Match.h"
#include <vector>

using namespace std;

//Class for storing stats of a particular team
class TeamManager
{
	int id;
	int wins;
	vector<Match> matches;	//Stores matches played by the team
public:
	void Initialize(int idi);
	int GetID();
	void AddMatch(bool result, Match match);
	vector<int> GetOpponents();
	vector<Match> GetMatches();
	int GetWins();
	int GetLosses();
	int GetMatchesCount();
	double GetMargin();
	double GetWinPerc(int &no);
};

