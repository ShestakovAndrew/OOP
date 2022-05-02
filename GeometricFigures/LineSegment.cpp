#include "LineSegment.h"

CLineSegment::CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor)
    :m_startPoint(startPoint), m_endPoint(endPoint), m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
    return 0.0;
}

double CLineSegment::GetPerimeter() const
{
    return 0.0;
}

std::string CLineSegment::ToString() const
{
    return std::string();
}

uint32_t CLineSegment::GetOutlineColor() const
{
    return uint32_t();
}

CPoint CLineSegment::GetStartPoint()
{
    return CPoint();
}

CPoint CLineSegment::GetEndPoint()
{
    return CPoint();
}
