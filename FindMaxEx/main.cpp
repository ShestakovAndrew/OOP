#include "FindMaxEx.h"
#include "Sportsman.h"
#include <iostream>
#include <sstream>

Sportsman GetSportsman(std::string const& str)
{
	Sportsman sportsman;
	std::istringstream ss(str);

	ss >> sportsman.name >> sportsman.height >> sportsman.weight;

	if (!ss) throw std::runtime_error("Invalid string.");

	return sportsman;
}

std::vector<Sportsman> ReadSportsmen(std::istream& input)
{
	std::vector<Sportsman> sportsmens;
	std::string inputStr;

	while (getline(input, inputStr))
	{
		try
		{
			sportsmens.push_back(GetSportsman(inputStr));
		}
		catch (std::runtime_error const& exc)
		{
			std::cout << exc.what() << std::endl;
		}
	}
	return sportsmens;
}

void PrintSportsmanWithMaxHeight(std::ostream& output, std::vector<Sportsman> const& sportsmen)
{
	Sportsman sportsmanWithMaxHeight;

	if (FindMax(sportsmen, sportsmanWithMaxHeight, IsLessHeight))
	{
		output << "Sportsman with max height: " << sportsmanWithMaxHeight.name
			<< std::endl << '\t' << "height: " << sportsmanWithMaxHeight.height
			<< std::endl << '\t' << "weight: " << sportsmanWithMaxHeight.weight << std::endl;
	}
	else
	{
		output << "Cannot find sportsman with max height." << std::endl;
	}
}

void PrintSportsmanWithMaxWeight(std::ostream& output, std::vector<Sportsman> const& sportsmen)
{
	Sportsman sportsmanWithMaxWeight;

	if (FindMax(sportsmen, sportsmanWithMaxWeight, IsLessWeight))
	{
		output << "Sportsman with max weight: " << sportsmanWithMaxWeight.name
			<< std::endl << '\t' << "height: " << sportsmanWithMaxWeight.height
			<< std::endl << '\t' << "weight: " << sportsmanWithMaxWeight.weight << std::endl;
	}
	else
	{
		output << "Cannot find sportsman with max weight" << std::endl;
	}
}

int main()
{
	std::vector<Sportsman> sportsmen = ReadSportsmen(std::cin);

	PrintSportsmanWithMaxHeight(std::cout, sportsmen);
	PrintSportsmanWithMaxWeight(std::cout, sportsmen);

	return 0;
}