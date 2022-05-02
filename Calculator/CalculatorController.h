#pragma once
#include "iostream"
#include <sstream>
#include <functional>

#include "Calculator.h"
#include "../termcolor.hpp"

namespace
{
	struct Arguments
	{
		std::optional<std::string> command;
		std::optional<std::string> identifier1;
		std::optional<std::string> identifier2;
		ÑFunction::Operation operation = ÑFunction::Operation::None;
		std::optional<std::string> identifier3;
	};
}

class CCalculatorController
{
public:
	CCalculatorController(CCalculator& calc, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	using Handler = std::function<void(Arguments const& action)>;
	using ActionMap = std::map<std::string, Handler>;

	void Var(Arguments const& commandFromUser);
	void Let(Arguments const& commandFromUser);
	void Fn(Arguments const& commandFromUser);
	void Print(Arguments const& commandFromUser);
	void Printvars(Arguments const& commandFromUser);
	void Printfns(Arguments const& commandFromUser);

	void PrintValues(CCalculator::Values const& values);
	void PrintOptionalValue(std::optional<double> value);

	CCalculator& m_calc;
	const ActionMap m_actionMap;
	std::istream& m_input;
	std::ostream& m_output;
};

