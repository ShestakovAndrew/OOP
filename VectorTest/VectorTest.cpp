#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Vector/Vector.h"

namespace
{
	bool TwoVectorsEqual(std::vector<double> const& first, std::vector<double> const& second)
	{
		return std::equal(first.begin(), first.end(), second.begin(),
			[](double const& value1, double const& value2)
			{
				constexpr double epsilon = 0.001;
				return std::fabs(value1 - value2) < epsilon;
			});
	}

	void RequireTwoDoubleVectors(std::vector<double> first, std::vector<double> const& second)
	{
		AddMeanPositiveNumberForAllElementsIn(first);
		REQUIRE(TwoVectorsEqual(first, second));
	}
}

TEST_CASE("Null vector should be equal null vector.")
{
	RequireTwoDoubleVectors({}, {});
}

TEST_CASE("Vector should be not changed.")
{
	RequireTwoDoubleVectors(
		{ 0 },
		{ 0 }
	);

	RequireTwoDoubleVectors(
		{ -3, -2, -1, -2, -1, -2, -3 }, 
		{ -3, -2, -1, -2, -1, -2, -3 }
	);

	RequireTwoDoubleVectors(
		{ -3.24632, -2.43242, -1.47237, 0, -1.4328, -2.24632, -3.24632 }, 
		{ -3.24632, -2.43242, -1.47237, 0, -1.4328, -2.24632, -3.24632 }
	);
}

TEST_CASE("Vector should be change.")
{
	RequireTwoDoubleVectors(
		{ 1.9 },
		{ 3.8 }
	);

	RequireTwoDoubleVectors(
		{ -3, -2, -1, 0, 1, 2, 3 },
		{ -1, 0, 1, 2, 3, 4, 5 }
	);

	RequireTwoDoubleVectors(
		{ -3.246, -2.432, -1.472, 0, 1.432, 2.246, 3.246 },
		{ -0.938, -0.124, 0.836, 2.308, 3.74, 4.554, 5.554 }
	);
}
