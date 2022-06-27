#define _USE_MATH_DEFINES
#include "Circle.h"

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center), m_radius(radius), m_outlineColor(outlineColor), m_fillColor(fillColor)
{
}

std::string CCircle::ToString() const
{
	std::stringstream sstream;

	sstream << std::fixed << std::setprecision(2)
		<< "Type shape: Circle" << std::endl
		<< "Perimeter: " << GetPerimeter() << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Center: " << m_center.ToString() << std::endl
		<< "Radius: " << m_radius << std::endl
		<< "Outline color: " << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor << std::endl
		<< "Fill color: " << std::hex << std::setw(6) << std::setfill('0') << m_fillColor;

	return sstream.str();
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

uint32_t CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.DrawCircle(m_center, m_radius, m_outlineColor);
	canvas.FillCircle(m_center, m_radius, m_fillColor);
}
