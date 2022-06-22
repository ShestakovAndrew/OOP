#include "LineSegment.h"

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
    :m_startPoint(startPoint), m_endPoint(endPoint), m_outlineColor(outlineColor)
{
}

std::string CLineSegment::ToString() const
{
	std::stringstream sstream;

	sstream << std::fixed << std::setprecision(2)
		<< "Type shape: Line Segment" << std::endl
		<< "Perimeter: " << GetPerimeter() << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Start point: " << m_startPoint.ToString() << std::endl
		<< "End point: " << m_endPoint.ToString() << std::endl
		<< "Outline color: " << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor;

	return sstream.str();
}

double CLineSegment::GetArea() const
{
    return 0;
}

double CLineSegment::GetPerimeter() const
{
    return sqrt(pow((m_endPoint.x - m_startPoint.x), 2) + pow((m_endPoint.y - m_startPoint.y), 2));
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint()
{
    return m_startPoint;
}

CPoint CLineSegment::GetEndPoint()
{
    return m_endPoint;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(m_startPoint, m_endPoint, m_outlineColor);
}
