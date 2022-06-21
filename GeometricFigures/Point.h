#pragma once
#include <string>
#include <sstream>
#include <iomanip>

class CPoint
{
public:
	double x;
	double y;

	std::string ToString() const;

	bool operator==(CPoint const& point) const;
};

