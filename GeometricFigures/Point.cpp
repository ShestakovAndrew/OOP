#include <sstream>
#include <iomanip>
#include "Point.h"

std::string CPoint::ToString() const
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << "[" << m_x << ", " << m_y << "]";
	return ss.str();
}
