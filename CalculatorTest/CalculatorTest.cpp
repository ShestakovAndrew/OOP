#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Calculator/Calculator.h"
#include <cmath>

TEST_CASE("Calculator variables and functions should be empty in start.")
{
	CCalculator calc;
	REQUIRE_NOTHROW(calc.GetValuesOfVariables().empty());
	REQUIRE_NOTHROW(calc.GetValuesOfFunctions().empty());
}

TEST_CASE("Var <identifier>")
{
	CCalculator calc;
	CCalculator::Values variables;

	SECTION("Should be successfully set variables.")
	{
		variables = {
			{ "x", std::nullopt }
		};

		calc.SetVariable("x");

		REQUIRE_NOTHROW(calc.GetValuesOfVariables() == variables);
	}

	SECTION("Should be notify that the variable already exists.")
	{
		REQUIRE_NOTHROW(calc.SetVariable("x"));
		REQUIRE_THROWS(calc.SetVariable("x"));

		WHEN("Function created")
		{
			REQUIRE_NOTHROW(calc.SetFunction("f1", "x"));

			THEN("Ñreating a variable named like a function should be return throws.")
			{
				REQUIRE_THROWS(calc.SetVariable("f1"));
			}
		}
	}

	SECTION("Should be return throws if error in name cariable.")
	{
		REQUIRE_THROWS(calc.SetVariable("1"));
		REQUIRE_THROWS(calc.SetVariable("1d"));
		REQUIRE_THROWS(calc.SetVariable(""));
		REQUIRE_NOTHROW(calc.SetVariable("_d"));
	}
}

TEST_CASE("Let <identifier> = (<double value> or <identifier2>)")
{
	CCalculator calc;
	CCalculator::Values variables, functions;

	SECTION("Should be creating a new variable.")
	{
		REQUIRE_NOTHROW(calc.GetValuesOfVariables().empty());
		REQUIRE_NOTHROW(calc.SetValueToVariable("x", 2));

		variables = {
			{"x", 2.00}
		};

		REQUIRE_NOTHROW(calc.GetValuesOfVariables() == variables);
	}

	SECTION("Should be assign to variable successfully.")
	{
		WHEN("Variable already created.")
		{
			variables = {
				{"x", 2.00},
				{"y", std::nullopt}
			};

			REQUIRE_NOTHROW(calc.SetVariable("y"));
			REQUIRE_NOTHROW(calc.GetValuesOfVariables() == variables);

			THEN("Should be assign a value to a variable.")
			{
				variables = {
					{"x", 2.00},
					{"y", 3.00}
				};

				REQUIRE_NOTHROW(calc.SetValueToVariable("y", 3));
				REQUIRE_NOTHROW(calc.GetValuesOfVariables() == variables);
			}

			AND_THEN("Should be reassign a value to a variable")
			{
				variables = {
					{"x", 2.00},
					{"y", 4.00}
				};

				REQUIRE_NOTHROW(calc.SetValueToVariable("y", 4));
				REQUIRE_NOTHROW(calc.GetValuesOfVariables() == variables);
			}

			AND_THEN("Should be assign the previously declared variable to the new variable")
			{
				variables = {
					{"x", 2.00},
					{"y", 4.00},
					{"z", 4.00}
				};

				REQUIRE_NOTHROW(calc.SetValueToVariable("z", "y"));
				REQUIRE_NOTHROW(calc.GetValuesOfVariables() == variables);
			}
		}
	}

	SECTION("Should not be assign to variable, when name collision.")
	{
		WHEN("Function created")
		{
			functions = {
				{"f1", 2.00}
			};

			calc.SetValueToVariable("x", 2);
			REQUIRE_NOTHROW(calc.SetFunction("f1", "x"));
			REQUIRE_NOTHROW(calc.GetValuesOfFunctions() == functions);

			THEN("Should not be declare a variable that matches a function name.")
			{
				REQUIRE_THROWS(calc.SetValueToVariable("f1", 1));
			}
		}
	}
}

TEST_CASE("Fn <identifier> = (<identifier2> or <identifier2><operation><identifier3>")
{
	CCalculator calc;
	CCalculator::Values variables, functions;

	SECTION("Should be declare a new function successfully.")
	{
		variables = {
			{"x", std::nullopt}
		};

		functions = {
			{"f1", std::nullopt}
		};

		REQUIRE_NOTHROW(calc.SetVariable("x"));
		REQUIRE_NOTHROW(calc.SetFunction("f1", "x"));

		REQUIRE_NOTHROW(calc.GetValuesOfVariables() == variables);
		REQUIRE_NOTHROW(calc.GetValuesOfFunctions() == functions);
	}

	SECTION("Should not be declare a new function if name collision.")
	{
		variables = {
			{"x", std::nullopt},
			{"f2", std::nullopt}
		};

		REQUIRE_NOTHROW(calc.SetVariable("f2"));
		REQUIRE_NOTHROW(calc.GetValuesOfVariables() == variables);

		REQUIRE_THROWS(calc.SetFunction("f2", "f1"));
	}

	SECTION("Should be declare a new function if the operation was successful.")
	{
		REQUIRE_NOTHROW(calc.SetValueToVariable("x", 10));
		REQUIRE_NOTHROW(calc.SetValueToVariable("y", 20));

		SECTION("Operation +")
		{
			REQUIRE_NOTHROW(calc.SetFunction("f1", "x", ÑFunction::Operation::Add, "y"));
			REQUIRE_NOTHROW(calc.SetFunction("f2", "f1", ÑFunction::Operation::Add, "f1"));

			REQUIRE(calc.GetValue("f1") == 30.00);
			REQUIRE(calc.GetValue("f2") == 60.00);
		}

		SECTION("Operation -")
		{
			REQUIRE_NOTHROW(calc.SetFunction("f3", "x", ÑFunction::Operation::Sub, "y"));
			REQUIRE_NOTHROW(calc.SetFunction("f4", "f3", ÑFunction::Operation::Sub, "f3"));

			REQUIRE(calc.GetValue("f3") == -10.00);
			REQUIRE(calc.GetValue("f4") == 0.00);
		}

		SECTION("Operation *")
		{
			REQUIRE_NOTHROW(calc.SetFunction("f5", "x", ÑFunction::Operation::Mult, "y"));
			REQUIRE_NOTHROW(calc.SetFunction("f6", "f5", ÑFunction::Operation::Mult, "f5"));

			REQUIRE(calc.GetValue("f5") == 200.00);
			REQUIRE(calc.GetValue("f6") == 40000.00);
		}

		SECTION("Operation /")
		{
			REQUIRE_NOTHROW(calc.SetFunction("f7", "x", ÑFunction::Operation::Div, "y"));
			REQUIRE_NOTHROW(calc.SetFunction("f8", "f7", ÑFunction::Operation::Div, "f7"));

			REQUIRE(calc.GetValue("f7") == 0.50);
			REQUIRE(calc.GetValue("f8") == 1.00);
		}

		SECTION("Operation / on zero")
		{
			REQUIRE_NOTHROW(calc.SetValueToVariable("z", 0));
			REQUIRE_THROWS(calc.SetFunction("f9", "f8", ÑFunction::Operation::Div, "z"));
			REQUIRE_THROWS(calc.GetValue("f9"));
		}
	}
}

TEST_CASE("Print <identifier>")
{
	CCalculator calc;

	SECTION("Should be print correct identifiers.")
	{
		REQUIRE_NOTHROW(calc.SetVariable("y"));
		REQUIRE_NOTHROW(calc.SetValueToVariable("x", 1.5));
		REQUIRE_NOTHROW(calc.SetFunction("f1", "x", ÑFunction::Operation::Mult, "x"));

		REQUIRE(calc.GetValue("y") == std::nullopt);
		REQUIRE(calc.GetValue("x") == 1.50);
		REQUIRE(calc.GetValue("f1") == 2.25);
		REQUIRE_THROWS(calc.GetValue("z"));
	}
}

TEST_CASE("Examples from document.")
{
	CCalculator calc;
	CCalculator::Values functions;
	CCalculator::Values variables;

	SECTION("Declaring, Assigning, and Displaying Variable Values.")
	{
		REQUIRE_NOTHROW(calc.SetVariable("x"));
		REQUIRE(calc.GetValue("x") == std::nullopt);
		REQUIRE_NOTHROW(calc.SetValueToVariable("x", 42));
		REQUIRE(calc.GetValue("x") == 42);
		REQUIRE_NOTHROW(calc.SetFunction("f1", "x", ÑFunction::Operation::Mult, "x"));
		REQUIRE_NOTHROW(calc.SetValueToVariable("x", 1.234));
		REQUIRE(calc.GetValue("x") == 1.234);
		REQUIRE_NOTHROW(calc.SetValueToVariable("y", "x"));
		REQUIRE_NOTHROW(calc.SetValueToVariable("x", 99));

		variables =
		{
			{"x", 99.00},
			{"y", 1.23}
		};

		REQUIRE_NOTHROW(calc.GetValuesOfVariables() == variables);
	}

	SECTION("Function declaration.")
	{
		REQUIRE_NOTHROW(calc.SetVariable("x"));
		REQUIRE_NOTHROW(calc.SetVariable("y"));
		REQUIRE_NOTHROW(calc.SetFunction("XPlusY", "x", ÑFunction::Operation::Add, "y"));
		REQUIRE(calc.GetValue("XPlusY") == std::nullopt);
		REQUIRE_NOTHROW(calc.SetValueToVariable("x", 3));
		REQUIRE_NOTHROW(calc.SetValueToVariable("y", 4));
		REQUIRE(calc.GetValue("XPlusY") == 7);
		REQUIRE_NOTHROW(calc.SetValueToVariable("x", 10));
		REQUIRE(calc.GetValue("XPlusY") == 14);
		REQUIRE_NOTHROW(calc.SetValueToVariable("z", 3.5));
		REQUIRE_NOTHROW(calc.SetFunction("XPlusYDivZ", "XPlusY", ÑFunction::Operation::Div, "z"));

		functions = {
			{"XPlusY", 14.00},
			{"XPlusYDivZ", 4.00}
		};

		REQUIRE_NOTHROW(calc.GetValuesOfFunctions() == functions);
	}

	SECTION("Once again about the difference between fn and let...")
	{
		REQUIRE_NOTHROW(calc.SetValueToVariable("v", 42));
		REQUIRE_NOTHROW(calc.SetValueToVariable("variable", "v"));
		REQUIRE_NOTHROW(calc.SetFunction("function", "v"));
		REQUIRE_NOTHROW(calc.SetValueToVariable("v", 43));
		REQUIRE(calc.GetValue("variable") == 42);
		REQUIRE(calc.GetValue("function") == 43);
	}

	SECTION("Calculating the area of a circle.")
	{
		REQUIRE_NOTHROW(calc.SetVariable("radius"));
		REQUIRE_NOTHROW(calc.SetValueToVariable("pi", 3.14159265));

		REQUIRE_NOTHROW(calc.SetFunction("radiusSquared", "radius", ÑFunction::Operation::Mult, "radius"));
		REQUIRE_NOTHROW(calc.SetFunction("circleArea", "pi", ÑFunction::Operation::Mult, "radiusSquared"));

		REQUIRE_NOTHROW(calc.SetValueToVariable("radius", 10));
		REQUIRE((round(calc.GetValue("circleArea").value() * 100) / 100) == 314.16);
		REQUIRE_NOTHROW(calc.SetValueToVariable("circle10Area", "circleArea"));
		REQUIRE_NOTHROW(calc.SetValueToVariable("radius", 20));
		REQUIRE_NOTHROW(calc.SetValueToVariable("circle20Area", "circleArea"));

		functions = {
			{"circleArea", 1256.64},
			{"nradiusSquared", 400.00}
		};

		REQUIRE_NOTHROW(calc.GetValuesOfFunctions() == functions);

		variables =
		{
			{"circle10Area", 314.16},
			{"circle20Area", 1256.64},
			{"pi", 3.14},
			{"radius", 20.00}
		};

		REQUIRE_NOTHROW(calc.GetValuesOfVariables() == variables);
	}

	SECTION("Computing the Fibonacci Sequence")
	{
		REQUIRE_NOTHROW(calc.SetValueToVariable("v0", 0));
		REQUIRE_NOTHROW(calc.SetValueToVariable("v1", 1));

		REQUIRE_NOTHROW(calc.SetFunction("fib0", "v0"));
		REQUIRE_NOTHROW(calc.SetFunction("fib1", "v1"));
		REQUIRE_NOTHROW(calc.SetFunction("fib2", "fib1", ÑFunction::Operation::Add, "fib0"));
		REQUIRE_NOTHROW(calc.SetFunction("fib3", "fib2", ÑFunction::Operation::Add, "fib1"));
		REQUIRE_NOTHROW(calc.SetFunction("fib4", "fib3", ÑFunction::Operation::Add, "fib2"));
		REQUIRE_NOTHROW(calc.SetFunction("fib5", "fib4", ÑFunction::Operation::Add, "fib3"));
		REQUIRE_NOTHROW(calc.SetFunction("fib6", "fib5", ÑFunction::Operation::Add, "fib4"));

		functions =	{
			{"fib0", 0},
			{"fib1", 1},
			{"fib2", 1},
			{"fib3", 2},
			{"fib4", 3},
			{"fib5", 5},
			{"fib6", 8}
		};

		REQUIRE_NOTHROW(calc.GetValuesOfFunctions() == functions);

		REQUIRE_NOTHROW(calc.SetValueToVariable("v0", 1));
		REQUIRE_NOTHROW(calc.SetValueToVariable("v1", 1));

		functions = {
			{"fib0", 1},
			{"fib1", 1},
			{"fib2", 2},
			{"fib3", 3},
			{"fib4", 5},
			{"fib5", 8},
			{"fib6", 13}
		};

		REQUIRE_NOTHROW(calc.GetValuesOfFunctions() == functions);
	}
}

//TEST_CASE("Ñalculation of large sequences of functions should be successfully.")
//{
//	CCalculator calc;
//	CCalculator::Values functions, variables;
//
//	REQUIRE_NOTHROW(calc.SetValueToVariable("x", 1));
//	REQUIRE_NOTHROW(calc.SetFunction("x2", "x", ÑFunction::Operation::Add, "x"));
//
//	for (size_t i = 3; i <= 1000000; i++)
//	{
//		REQUIRE_NOTHROW(calc.SetFunction("x" + std::to_string(i), "x" + std::to_string(i - 1), ÑFunction::Operation::Add, "x"));
//	}
//
//	REQUIRE(calc.GetValue("x1000000") == 1000000.00);	
//	REQUIRE_NOTHROW(calc.SetValueToVariable("x", 2));
//	REQUIRE(calc.GetValue("x1000000") == 2000000.00);
//}