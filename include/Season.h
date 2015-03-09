#pragma once
#include <unordered_map>

using namespace std;

//Class for storing Season mapping against there id
class Season
{
	unordered_map<string, char> seasonid;
public:
	Season();
	char GetSeasonID(string year);
};

