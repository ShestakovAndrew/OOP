#include "LineSegment.h"

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
    :m_startPoint(startPoint), m_endPoint(endPoint), m_outlineColor(outlineColor)
{
}

std::string CLineSegment::ToString() const
{
    return std::string();
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
