#include "SeasonManager.h"
#include <iostream>
#include <fstream>
#include <string>

//Initializes all teams stats
SeasonManager::SeasonManager()
{
	vector<int> all_teams = teams.GetAllTeams();

	for(const auto& i : all_teams)
	{
		TeamManager temp;
		temp.Initialize(i);
		teams_stats[i] = temp;
	}
}

//Loads a particular season matches into teams_stats
bool SeasonManager::LoadSeason(string season)
{
	char id = seasons.GetSeasonID(season);

	if (!id)
	{
		cout << "Season Not Found";
		return false;
	}

	ifstream file;
	file.open("../data/regular_tourney_combined_results.csv");

	string value;

	string temp;
	getline(file, temp);

	while (file.good())
	{
		Match match;

		getline(file, value, ',');

		match.season = value[0];

		if (match.season != id || !match.season )
		{
			getline(file, value);
			continue;
		}

		getline(file, value, ',');
		match.daynumber = stoi(value);
		getline(file, value, ',');
		match.winid = stoi(value);
		getline(file, value, ',');
		match.winscore = stoi(value);
		getline(file, value, ',');
		match.loseid = stoi(value);
		getline(file, value, ',');
		match.losescore = stoi(value);
		getline(file, value);
		match.location = value[0];

		//Add match to both winning and lossing teams matches while specifying wether won or lost
		teams_stats[match.winid].AddMatch(true, match);
		teams_stats[match.loseid].AddMatch(false, match);
	}

	file.close();

	return true;
}

//Calculates Team with highest RPI in season
void SeasonManager::RPIChampion(string season)
{
	if (!LoadSeason(season))	//Load the season
		return;

	double max = 0;	//For storing max rpi value
	int max_id = 0;

	//Iterate over all the teams
	for (auto it = teams_stats.begin(); it != teams_stats.end(); ++it)
	{
		int id = it->first;
		TeamManager team = it->second;

		double rpi = 0;
		double opponents_rpi = 0;
		double opponents_opponents_rpi = 0;

		int opponents_wins = 0;
		int opponents_losses = 0;

		int opponents_opponents_wins = 0;
		int opponents_opponents_losses = 0;

		int no = 0;

		rpi += 0.25 * team.GetWinPerc(no);	//Get teams winning percentage

		//If a team played no match then n=0 in which case the team is neglected
		if (no == 0)
			continue;

		vector<int> opponents = team.GetOpponents();	//Gets a teams opponents

		for(const auto& i : opponents)
		{

			opponents_wins += teams_stats[i].GetWins();	//Adds opponents wins
			opponents_losses += teams_stats[i].GetMatchesCount();	//Adds opponents matches

			vector<int> opponents_opponents = teams_stats[i].GetOpponents();	//Gets opponents opponents
			for(const auto& j : opponents_opponents)
			{
				opponents_opponents_wins += teams_stats[j].GetWins();	//Adds opponents opponents wins
				opponents_opponents_losses += teams_stats[j].GetMatchesCount();	//Adds opponents opponents matches
			}
		}

		opponents_rpi = (double)opponents_wins / opponents_losses;	//Opponents RPI

		rpi += 0.5 * opponents_rpi;		//Add to original RPI

		opponents_opponents_rpi = (double)opponents_opponents_wins / opponents_opponents_losses;	//Opponents opponents RPI

		rpi += 0.25 * opponents_opponents_rpi;	//Add to original RPI

		//Check if its the highest rpi yet
		if (rpi > max)
		{
			max_id = id;
			max = rpi;
		}
	}

	cout << teams.GetTeam(max_id) << endl;

}

//Lists all games played by a team in a season
void SeasonManager::ListGames(string season, string team)
{
	if (!LoadSeason(season))
		return;

	int team_id = teams.GetTeamID(team);

	vector<Match> matches = teams_stats[team_id].GetMatches();

	for(const auto&  i : matches)
	{
		if (team_id == i.winid)
			cout << "W " << teams.GetTeam(i.loseid) << " " << i.winscore << "-" << i.losescore << endl;	//If team wins
		else
			cout << "L " << teams.GetTeam(i.winid) << " " << i.losescore << "-" << i.winscore << endl;	//If team loses
	}
}

//Final game record for a team in a season
void SeasonManager::FinalRecord(string season, string team)
{
	if (!LoadSeason(season))
		return;

	int team_id = teams.GetTeamID(team);

	cout << teams_stats[team_id].GetWins() << "-" << teams_stats[team_id].GetLosses() << endl;	//Wins-Loses
}

//Best Win Percentage of a team
void SeasonManager::BestWinPercentage(string season)
{
	if (!LoadSeason(season))
		return;

	int n;
	double max = 0;
	int max_id = 0;

	//Iterates over all teams
	for (auto it = teams_stats.begin(); it != teams_stats.end(); ++it)
	{
		double win_perc = it->second.GetWinPerc(n);
		if (n == 0)
			continue;

		//Checks if winning percentage is highest yet, if same as previous highest then checks which has a higher ID number
		if (win_perc > max || (win_perc==max && it->first>max_id))
		{
			max = win_perc;
			max_id = it->first;
		}
	}
	cout << teams.GetTeam(max_id)<<endl;
}

//Shows team with highest margin
void SeasonManager::LargestMargin(string season)
{
	if (!LoadSeason(season))
		return;

	double max = -1000.0;	//Initial negative value
	int max_id = 0;

	//ITerate over all teams
	for (auto it = teams_stats.begin(); it != teams_stats.end(); ++it)
	{
		//Checks if margin is highest yet
		if (it->second.GetMargin() > max)
		{
			max_id = it->first;
			max = it->second.GetMargin();
		}
	}

	cout << teams.GetTeam(max_id)<<endl;
}