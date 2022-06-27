#pragma once
#include <string>

struct Sportsman
{
	std::string name;
	double height = 0;
	double weight = 0;
};

bool IsLessHeight(const Sportsman& s1, const Sportsman& s2)
{
	return s1.height < s2.height;
}

bool IsLessWeight(const Sportsman& s1, const Sportsman& s2)
{
	return s1.weight < s2.weight;
}