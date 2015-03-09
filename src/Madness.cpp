#include "SeasonManager.h"
#include <cstring>
using namespace std;

int main(int argc, char* argv[])
{
	SeasonManager madness;

	string season_name = string(argv[2]);

	string team_name = string(argv[3]);

	//Handling multiple worded teams
	for (int i = 4; i<argc; i++)
		team_name += " " + string(argv[i]);

	if (strcmp(argv[1], "rpiChampion") == 0)
		madness.RPIChampion(season_name);
	else if (strcmp(argv[1], "list") == 0)
		madness.ListGames(season_name, team_name);
	else if (strcmp(argv[1], "finalRecord") == 0)
		madness.FinalRecord(season_name, team_name);
	else if (strcmp(argv[1], "bestWinPercentage") == 0)
		madness.BestWinPercentage(season_name);
	else if (strcmp(argv[1], "largestMargin") == 0)
		madness.LargestMargin(season_name);
}