#include "Circle.h"

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center), m_radius(radius), m_outlineColor(outlineColor), m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return 0.0;
}

double CCircle::GetPerimeter() const
{
	return 0.0;
}

std::string CCircle::ToString() const
{
	return std::string();
}

uint32_t CCircle::GetOutlineColor() const
{
	return uint32_t();
}

uint32_t CCircle::GetFillColor() const
{
	return uint32_t();
}

CPoint CCircle::GetCenter() const
{
	return CPoint();
}

double CCircle::GetRadius() const
{
	return 0.0;
}
