#pragma once
#include <optional>

class CVariable
{
public:

	CVariable();
	void SetValue(std::optional<double> value);
	std::optional<double> GetValue() const;

private:
	std::optional<double> m_value;
};

