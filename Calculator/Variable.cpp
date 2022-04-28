#include "Variable.h"

CVariable::CVariable()
	:m_value(std::nullopt)
{
}

void CVariable::SetValue(std::optional<double> value)
{
	m_value = value;
}

std::optional<double> CVariable::GetValue() const
{
	return m_value;
}
