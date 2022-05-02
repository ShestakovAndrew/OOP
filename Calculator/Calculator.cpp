#include "Calculator.h"
#include <stdexcept>
#include <regex>
#include <iostream>
#include <set>

namespace
{
	bool IsValidSymbol(char const& ch)
	{
		std::string symbol(1, ch);
		return std::regex_match(symbol, std::regex("\\w"));
	}

	bool CheckNameIdentifier(std::string const& identifier)
	{
		if (identifier.empty() or
			std::isdigit(identifier[0]) or
			!std::all_of(identifier.begin(), identifier.end(), IsValidSymbol)
		)
		{
			throw std::exception("Bad name of identifier.");
		}
		return true;
	}

	bool CheckCorrectValues(
		std::optional<double> const& valueOfIdentifier1,
		ÑFunction::Operation const& operation,
		std::optional<double> const& valueOfIdentifier2
	)
	{
		return (!valueOfIdentifier1.has_value()) or (!valueOfIdentifier2.has_value()) or 
			(operation == ÑFunction::Operation::Div and valueOfIdentifier2.value() == 0);
	}
}

CCalculator::Values CCalculator::GetValuesOfVariables() const
{
	Values valuesOfVariables;

	for (auto const& [identifier, variable] : m_variables)
	{
		valuesOfVariables.emplace(identifier, variable.GetValue());
	}

	return valuesOfVariables;
}

CCalculator::Values CCalculator::GetValuesOfFunctions() const
{
	Values valuesOfFunctions;

	for (auto const& [identifier, function] : m_functions)
	{
		valuesOfFunctions.emplace(identifier, function.GetValue());
	}

	return valuesOfFunctions;
}

std::optional<double> CCalculator::GetValue(std::string const& identifier) const
{
	if (IsFunctionNameExists(identifier))
	{
		ÑFunction function = m_functions.find(identifier)->second;
		return function.GetValue();
	}

	if (IsVariableNameExists(identifier))
	{
		CVariable variable = m_variables.find(identifier)->second;
		return variable.GetValue();
	}

	throw std::exception("Identifier does not exist.");
}

bool CCalculator::IsVariableNameExists(std::string const& identifier) const
{
	return m_variables.find(identifier) != m_variables.end();
}

bool CCalculator::IsFunctionNameExists(std::string const& identifier) const
{
	return m_functions.find(identifier) != m_functions.end();
}

void CCalculator::CheckExistenceIdentifier(std::string const& identifier) const
{
	if (IsVariableNameExists(identifier))
	{
		throw std::exception("Variable with the same identifier already exists.");
	}

	if (IsFunctionNameExists(identifier))
	{
		throw std::exception("Function with the same identifier already exists.");
	}
}

void CCalculator::CheckNonExistenceIdentifier(std::string const& identifier) const
{
	if (!IsVariableNameExists(identifier) and !IsFunctionNameExists(identifier))
	{
		throw std::exception("Identifier not found.");
	}
}

void CCalculator::SetVariable(std::string const& identifier)
{
	CheckExistenceIdentifier(identifier);
	CheckNameIdentifier(identifier);
	m_variables.emplace(identifier, CVariable());
}

void CCalculator::SetValueToVariable(std::string const& identifier, double value)
{
	if (!IsVariableNameExists(identifier)) SetVariable(identifier);
	m_variables[identifier].SetValue(value);
	RecalculationFunction(identifier);
}

void CCalculator::SetValueToVariable(std::string const& identifier1, std::string const& identifier2)
{
	CheckNonExistenceIdentifier(identifier2);
	if (!IsVariableNameExists(identifier1)) SetVariable(identifier1);
	m_variables[identifier1].SetValue(GetValue(identifier2));
	RecalculationFunction(identifier1);
}

void CCalculator::SetFunction(std::string const& identifier1, std::string const& identifier2)
{
	CheckExistenceIdentifier(identifier1);
	CheckNameIdentifier(identifier1);
	CheckNonExistenceIdentifier(identifier2);

	m_functions.emplace(identifier1, ÑFunction(identifier2));
	m_functions[identifier1].SetValue(GetValue(identifier2));
	m_functionSequence.push_back(identifier1);
}

void CCalculator::SetFunction(
	std::string const& identifier1,
	std::string const& identifier2,
	ÑFunction::Operation const& operation,
	std::string const& identifier3
)
{
	CheckNameIdentifier(identifier1);
	CheckExistenceIdentifier(identifier1);

	CheckNonExistenceIdentifier(identifier2);
	CheckNonExistenceIdentifier(identifier3);

	m_functions.emplace(identifier1, ÑFunction(identifier2, operation, identifier3));
	m_functions[identifier1].SetValue(ComputeFunctionValue(m_functions[identifier1]));
	m_functionSequence.push_back(identifier1);
}

std::optional<double> CCalculator::ComputeFunctionValue(ÑFunction function)
{
	std::optional<double> valueOfIdentifier1 = GetValue(function.GetIdentifier1());

	ÑFunction::Operation operation = function.GetOperation();

	if (operation == ÑFunction::Operation::None) return valueOfIdentifier1;

	std::optional<double> valueOfIdentifier2 = GetValue(function.GetIdentifier2());

	if (CheckCorrectValues(valueOfIdentifier1, operation, valueOfIdentifier2))
	{
		return std::nullopt;
	}

	switch (operation)
	{
		case ÑFunction::Operation::Add: {
			return valueOfIdentifier1.value() + valueOfIdentifier2.value();
		}
		case ÑFunction::Operation::Sub: {
			return valueOfIdentifier1.value() - valueOfIdentifier2.value();
		}
		case ÑFunction::Operation::Mult: {
			return valueOfIdentifier1.value() * valueOfIdentifier2.value();
		}
		case ÑFunction::Operation::Div: {
			return valueOfIdentifier1.value() / valueOfIdentifier2.value();
		}
		default: {
			return std::nullopt;
		}
	}
}

void CCalculator::RecalculationFunction(std::string const& changedIdentifier)
{
	std::set<std::string> changedFunctions;
	changedFunctions.insert(changedIdentifier);

	for (auto const& functionIdentifier : m_functionSequence)
	{
		ÑFunction& function = m_functions[functionIdentifier];
		if (changedFunctions.count(functionIdentifier) == 0 and 
			(changedFunctions.count(function.GetIdentifier1()) != 0 or changedFunctions.count(function.GetIdentifier2()) != 0))
		{
			changedFunctions.emplace(functionIdentifier);
			function.SetValue(ComputeFunctionValue(function));
		}
	}
}
