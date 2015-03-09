#include "Season.h"
#include <fstream>
#include <string>
#include <iostream>

//Loads season data in constructor
Season::Season()
{
	ifstream file;
	file.open("../data/seasons.csv");

	string idstring;
	string year;

	string temp;
	getline(file, temp);

	while (file.good())
	{
		getline(file, idstring, ',');
		getline(file, year);

		char id = idstring[0];

		seasonid[year] = id;
	}
	file.close();
}

//Returns season ID from name
char Season::GetSeasonID(string year)
{
	return seasonid[year];
}