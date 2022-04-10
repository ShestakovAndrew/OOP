#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "GeneratorSimplesNumbers/GeneratorSimplesNumbers.h"

TEST_CASE("GeneratePrimeNumbersSet test")
{
	std::set<size_t> primalNumbers;

	SECTION("In range 0 should be 0 prime numbers.")
	{
		primalNumbers = GeneratePrimeNumbersSet(0);
		REQUIRE(primalNumbers.size() == 0);
	}

	SECTION("In range from 1 to 100000000 should be 5761455 prime numbers.")
	{
		primalNumbers = GeneratePrimeNumbersSet(100'000'000);
		REQUIRE(primalNumbers.size() == 5761455);
	}
}