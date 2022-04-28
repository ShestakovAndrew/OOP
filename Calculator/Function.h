#pragma once
#include <optional>
#include <string>

class ÑFunction
{
public:
	enum class Operation
	{
		Add,
		Sub,
		Div,
		Mult,
		None
	};

	ÑFunction();
	ÑFunction(std::string const& identifier);
	ÑFunction(std::string const& identifier1, Operation const& operation, std::string const& identifier2);

	void SetValue(std::optional<double> value);

	std::string GetIdentifier1() const;
	Operation GetOperation() const;
	std::string GetIdentifier2() const;
	std::optional<double> GetValue() const;

private:
	std::string m_identifier1;
	Operation m_operation;
	std::string m_identifier2;
	std::optional<double> m_value;
};

