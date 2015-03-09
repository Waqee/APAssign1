#include "SeasonManager.h"
#include <cstring>
using namespace std;

int main(int argc, char* argv[])
{
	SeasonManager madness;

	if (strcmp(argv[1], "rpiChampion") == 0)
		madness.RPIChampion(string(argv[2]));
	else if (strcmp(argv[1], "list") == 0)
		madness.ListGames(string(argv[2]), string(argv[3]));
	else if (strcmp(argv[1], "finalRecord") == 0)
		madness.FinalRecord(string(argv[2]), string(argv[3]));
	else if (strcmp(argv[1], "bestWinPercentage") == 0)
		madness.BestWinPercentage(string(argv[2]));
	else if (strcmp(argv[1], "largestMargin") == 0)
		madness.LargestMargin(string(argv[2]));
}