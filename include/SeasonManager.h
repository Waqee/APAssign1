#pragma once
#include "Team.h"
#include "Season.h"
#include "TeamManager.h"
#include <unordered_map>

//Class that displays the season stats, it is the main class used by madness
class SeasonManager
{
	Season seasons;
	Team teams;
	unordered_map<int, TeamManager> teams_stats;		//Stores Team stats of all teams
public:
	SeasonManager();
	bool LoadSeason(string season);
	void RPIChampion(string season);
	void ListGames(string season, string team);
	void FinalRecord(string season, string team);
	void BestWinPercentage(string season);
	void LargestMargin(string season);
};

