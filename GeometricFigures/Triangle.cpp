#include "Triangle.h"

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
	:m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3), m_outlineColor(outlineColor), m_fillColor(fillColor)
{
}

double CTriangle::GetArea() const
{
	return 0.0;
}

double CTriangle::GetPerimeter() const
{
	return 0.0;
}

std::string CTriangle::ToString() const
{
	return std::string();
}

uint32_t CTriangle::GetOutlineColor() const
{
	return uint32_t();
}

uint32_t CTriangle::GetFillColor() const
{
	return uint32_t();
}

CPoint CTriangle::GetVertex1() const
{
	return CPoint();
}

CPoint CTriangle::GetVertex2() const
{
	return CPoint();
}

CPoint CTriangle::GetVertex3() const
{
	return CPoint();
}
