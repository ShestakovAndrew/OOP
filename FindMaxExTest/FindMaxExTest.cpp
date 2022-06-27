#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include "FindMaxEx/FindMaxEx.h"
#include "FindMaxEx/Sportsman.h"

namespace
{
	std::vector<Sportsman> sportsmans = {
		{ "Andrey", 182, 66 },
		{ "Dima", 185, 72 },
		{ "Ivan", 174, 77 }
	};
}

TEST_CASE("FindMax() should find the maximum value of vector<double>")
{
	std::vector<double> doubleVector = { 9.2, 17.12, 15.1, 40.7};

	double maxValue;
	REQUIRE(FindMax(doubleVector, maxValue, std::less<double>()));
	REQUIRE(maxValue == 40.7);
}

TEST_CASE("FindMax() should find the maximum value of vector<char>")
{
	std::vector<char> charVector = { 'a', 'b', 'z', 'y' };
	char maxValue;
	REQUIRE(FindMax(charVector, maxValue, std::less<char>()));
	REQUIRE(maxValue == 'z');
}

TEST_CASE("If vector<T> is empty, FindMax() must return false")
{
	std::vector<int> intVector;
	int maxValue;
	REQUIRE_FALSE(FindMax(intVector, maxValue, std::less<int>()));
}

TEST_CASE("FindMax() must find sporstman with max height in vector<Sportsman>")
{
	Sportsman sportsman;

	REQUIRE(FindMax(sportsmans, sportsman, IsLessHeight));
	REQUIRE(sportsman.name == "Dima");
	REQUIRE(sportsman.height == 185);
	REQUIRE(sportsman.weight == 72);
}

TEST_CASE("FindMax() must find sporstman with max weight in vector<Sportsman>")
{
	Sportsman sportsman;

	REQUIRE(FindMax(sportsmans, sportsman, IsLessWeight));
	REQUIRE(sportsman.name == "Ivan");
	REQUIRE(sportsman.height == 174);
	REQUIRE(sportsman.weight == 77);
}