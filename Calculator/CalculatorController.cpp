#include "CalculatorController.h"

CCalculatorController::CCalculatorController(CCalculator& calc, std::istream& input, std::ostream& output)
	:m_calc(calc), m_input(input), m_output(output)
{
}

bool CCalculatorController::HandleCommand()
{
	return false;
}

void CCalculatorController::Var(std::string const& identifier)
{
}

void CCalculatorController::Let(std::string const& action)
{
}

void CCalculatorController::Fn(std::string const& action)
{
}

void CCalculatorController::Print(std::string const& identifier)
{
}

void CCalculatorController::Printvars()
{
}

void CCalculatorController::Printfns()
{
}
