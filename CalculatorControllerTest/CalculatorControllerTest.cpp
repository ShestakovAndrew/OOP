#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Calculator/Calculator.h"
#include <Calculator/CalculatorController.h>

void VerifyCommandHandling(std::string const& command, std::string const& expectedResult, CCalculator& calc)
{
	std::stringstream input, output;
	CCalculatorController controller(calc, input, output);
	input << command;
	REQUIRE(controller.HandleCommand());
	REQUIRE(expectedResult == output.str());
}
