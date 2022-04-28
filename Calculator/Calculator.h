#pragma once
#include <optional>
#include <map>
#include <vector>
#include "Variable.h"
#include "Function.h"

class CCalculator
{
public:

	using Values = std::map<std::string, std::optional<double>>;
	using Variables = std::map<std::string, CVariable>;
	using Functions = std::map<std::string, ÑFunction>;

	void SetVariable(std::string const& identifier);

	void SetValueToVariable(std::string const& identifier, double value);
	void SetValueToVariable(std::string const& identifier1, std::string const& identifier2);

	void SetFunction(std::string const& identifier1, std::string const& identifier2);
	void SetFunction(std::string const& identifier1,
		std::string const& identifier2,
		ÑFunction::Operation const& operation,
		std::string const& identifier3
	);

	Values GetValuesOfVariables() const;
	Values GetValuesOfFunctions() const;
	std::optional<double> GetValue(std::string const& identifier) const;
	
private:
	Variables m_variables;
	Functions m_functions;
	std::vector<std::string> m_functionSequence;

	bool IsFunctionNameExists(std::string const& identifier) const;
	bool IsVariableNameExists(std::string const& identifier) const;
	void CheckExistenceIdentifier(std::string const& identifier) const;
	void CheckNonExistenceIdentifier(std::string const& identifier) const;
	std::optional<double> ComputeFunctionValue(ÑFunction function);
	void RecalculationFunction(std::string const& identifier);
};

