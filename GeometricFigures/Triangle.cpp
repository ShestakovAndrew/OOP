#include "Triangle.h"

namespace
{
	double LengthOf(CPoint point1, CPoint point2)
	{
		return sqrt(pow((point1.x - point2.x), 2) + pow((point1.y - point2.y), 2));
	}
}

CTriangle::CTriangle(CPoint vertex1, CPoint vertex2, CPoint vertex3, uint32_t outlineColor, uint32_t fillColor)
	:m_vertex1(vertex1), m_vertex2(vertex2), m_vertex3(vertex3), m_outlineColor(outlineColor), m_fillColor(fillColor)
{
}

std::string CTriangle::ToString() const
{
	return std::string();
}

double CTriangle::GetArea() const
{
	return 0.5 * abs(
		m_vertex1.x * (m_vertex2.y - m_vertex3.y) +
		m_vertex2.x * (m_vertex3.y - m_vertex1.y) +
		m_vertex3.x * (m_vertex1.y - m_vertex2.y)
	);
}

double CTriangle::GetPerimeter() const
{
	return LengthOf(m_vertex1, m_vertex2) + LengthOf(m_vertex2, m_vertex3) + LengthOf(m_vertex1, m_vertex3);
}

uint32_t CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}
