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

TEST_CASE("Handle command Var.")
{
	CCalculator calc;
	VerifyCommandHandling("var x", "", calc);
	VerifyCommandHandling("var y", "", calc);
	VerifyCommandHandling("var y", "Error: Variable with the same identifier already exists.\n", calc);
	VerifyCommandHandling("var", "Error: Bad name of identifier.\n", calc);
	VerifyCommandHandling("var 1", "Error: Bad name of identifier.\n", calc);
}

TEST_CASE("Handle command Let.")
{
	CCalculator calc;

	SECTION("Let set value.")
	{
		VerifyCommandHandling("let x = 2", "", calc);
		VerifyCommandHandling("let y = 1.2323", "", calc);
		VerifyCommandHandling("let 1 = 1.233", "Error: Bad name of identifier.\n", calc);
	}

	SECTION("Let set identifier.")
	{
		VerifyCommandHandling("var x", "", calc);
		VerifyCommandHandling("var y", "", calc);
		VerifyCommandHandling("let z = x", "", calc);
		VerifyCommandHandling("let r = e", "Error: Identifier not found.\n", calc);
	}
}

TEST_CASE("Handle command Fn")
{
	CCalculator calc;

	SECTION("Fn set identifire.")
	{
		VerifyCommandHandling("var x", "", calc);
		VerifyCommandHandling("fn x = x", "Error: Variable with the same identifier already exists.\n", calc);
		VerifyCommandHandling("fn y = x", "", calc);
		VerifyCommandHandling("fn y = x", "Error: Function with the same identifier already exists.\n", calc);
		VerifyCommandHandling("fn 1 = x", "Error: Bad name of identifier.\n", calc);
		VerifyCommandHandling("fn  = x", "Error: Bad name of identifier.\n", calc);
		VerifyCommandHandling("fn f1 = o", "Error: Identifier not found.\n", calc);
	}

	SECTION("Fn calculate with operation.")
	{
		VerifyCommandHandling("let x = 1", "", calc);
		VerifyCommandHandling("fn 1 = x + x", "Error: Bad name of identifier.\n", calc);
		VerifyCommandHandling("fn  = x + x", "Error: Bad name of identifier.\n", calc);
		VerifyCommandHandling("fn x = x + x", "Error: Variable with the same identifier already exists.\n", calc);
		VerifyCommandHandling("fn y = x + x", "", calc);
		VerifyCommandHandling("fn f1 = x + x", "", calc);
		VerifyCommandHandling("fn f2 = x - x", "", calc);
		VerifyCommandHandling("fn f3 = x * x", "", calc);
		VerifyCommandHandling("fn f4 = x / x", "", calc);
		VerifyCommandHandling("fn y = x + x", "Error: Function with the same identifier already exists.\n", calc);
		VerifyCommandHandling("fn z = o + x", "Error: Identifier not found.\n", calc);
	}
}

TEST_CASE("Handle command Print")
{
	CCalculator calc;
	calc.SetValueToVariable("x", 22.25);
	VerifyCommandHandling("print x", "22.25\n", calc);

	calc.SetFunction("f1", "x", ÑFunction::Operation::Add, "x");
	VerifyCommandHandling("print f1", "44.50\n", calc);
}

TEST_CASE("Handle command Printvars")
{
	CCalculator calc;
	calc.SetValueToVariable("b", 2);
	calc.SetValueToVariable("c", 3);
	calc.SetValueToVariable("a", 1);
	calc.SetVariable("d");
	VerifyCommandHandling("printvars", "a:1.00\nb:2.00\nc:3.00\nd:nan\n", calc);
}

TEST_CASE("Handle command Printfns")
{
	CCalculator calc;

	calc.SetValueToVariable("one", 1);
	calc.SetValueToVariable("zero", 0);

	calc.SetVariable("nan");

	calc.SetFunction("f1", "one", ÑFunction::Operation::Sub, "nan");
	calc.SetFunction("f2", "one", ÑFunction::Operation::Div, "zero");
	calc.SetFunction("f3", "one", ÑFunction::Operation::Add, "zero");

	VerifyCommandHandling("printfns", "f1:nan\nf2:nan\nf3:1.00\n", calc);
}

TEST_CASE("If command is invalid then handle command must return false")
{
	CCalculator calc;
	std::stringstream input, output;
	CCalculatorController controller(calc, input, output);
	input << "invalid command";
	REQUIRE_FALSE(controller.HandleCommand());
}


