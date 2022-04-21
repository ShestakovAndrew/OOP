#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "GeneratorSimplesNumbers/GeneratorSimplesNumbers.h"

TEST_CASE("GeneratePrimeNumbersSet Test")
{
	std::set<size_t> primalNumbers = {};

	SECTION("If upper bound < 2")
	{
		REQUIRE(GeneratePrimeNumbersSet(0) == primalNumbers);
		REQUIRE(GeneratePrimeNumbersSet(1) == primalNumbers);
		REQUIRE(GeneratePrimeNumbersSet(-1) == primalNumbers);
	}

	SECTION("If upper bound >= 2")
	{
		primalNumbers = { 2 };
		REQUIRE(GeneratePrimeNumbersSet(2) == primalNumbers);

		primalNumbers = { 2, 3 };
		REQUIRE(GeneratePrimeNumbersSet(3) == primalNumbers);
		REQUIRE(GeneratePrimeNumbersSet(4) == primalNumbers);

		primalNumbers = { 2, 3, 5, 7, 11 };
		REQUIRE(GeneratePrimeNumbersSet(11) == primalNumbers);
	}

#if (!_DEBUG)
	SECTION("In range from 1 to 100000000 should be 5761455 prime numbers.")
	{
		REQUIRE(GeneratePrimeNumbersSet(100'000'000).size() == 5761455);
	}
#endif
}

