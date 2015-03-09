#include "TeamManager.h"
#include <iostream>

//Initializes the Team Manager object
void TeamManager::Initialize(int idi)
{
	id = idi;
	wins = 0;
}

//Resturs ID of a team
int TeamManager::GetID()
{
	return id;
}

//Add a match to teams matches
void TeamManager::AddMatch(bool result, Match match)
{
	if (result)
		wins++;
	matches.push_back(match);
}

//Gets list of opponent ids faced by the team
vector<int> TeamManager::GetOpponents()
{
	vector<int> opponents;

	for(const auto& i : matches)
	{
		if (i.winid == id)
			opponents.push_back(i.loseid);
		else
			opponents.push_back(i.winid);
	}

	return opponents;
}

//Returns matches
vector<Match> TeamManager::GetMatches()
{
	return matches;
}

//Returns wins
int TeamManager::GetWins()
{
	return wins;
}

//Returns losses
int TeamManager::GetLosses()
{
	return matches.size() - wins;
}

//Returns total number of matches
int TeamManager::GetMatchesCount()
{
	return matches.size();
}

//Returns goals scored - goals allowed during all matches to get margin
double TeamManager::GetMargin()
{
	int scored = 0;
	int allowed = 0;

	if (matches.size() == 0)
		return 0;

	for(const auto& i : matches)
	{
		if (i.winid == id)
		{
			scored += i.winscore;
			allowed += i.losescore;
		}
		else
		{
			scored += i.losescore;
			allowed += i.winscore;
		}
	}

	return (double)(scored - allowed) / matches.size();
}

//Returns win percentage 
double TeamManager::GetWinPerc(int &no)
{
	no = matches.size();
	return (double)wins / matches.size();
}