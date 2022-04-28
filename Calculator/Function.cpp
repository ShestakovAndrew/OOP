#include "Function.h"

ÑFunction::ÑFunction()
{
}

ÑFunction::ÑFunction(std::string const& identifier)
	: m_identifier1(identifier), m_operation(ÑFunction::Operation::None), m_value(std::nullopt)
{
}

ÑFunction::ÑFunction(std::string const& identifier1, Operation const& operation, std::string const& identifier2)
	: m_identifier1(identifier1), m_operation(operation), m_identifier2(identifier2), m_value(std::nullopt)
{
}

void ÑFunction::SetValue(std::optional<double> value)
{
	m_value = value;
}

std::optional<double> ÑFunction::GetValue() const
{
	return m_value;
}

std::string ÑFunction::GetIdentifier1() const
{
	return m_identifier1;
}

ÑFunction::Operation ÑFunction::GetOperation() const
{
	return m_operation;
}

std::string ÑFunction::GetIdentifier2() const
{
	return m_identifier2;
}
