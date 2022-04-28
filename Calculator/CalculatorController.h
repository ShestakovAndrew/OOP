#pragma once
#include "iostream"
#include "Calculator.h"

class CCalculatorController
{
public:
	CCalculatorController(CCalculator& calc, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	void Var(std::string const& identifier);
	void Let(std::string const& action);
	void Fn(std::string const& action);
	void Print(std::string const& identifier);
	void Printvars();
	void Printfns();

	CCalculator& m_calc;
	std::istream& m_input;
	std::ostream& m_output;
};

