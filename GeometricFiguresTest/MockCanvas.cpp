#include "MockCanvas.h"

void CMockCanvas::DrawLine(CPoint const& from, CPoint const& to, uint32_t lineColor)
{
	m_data.push_back(Method::DrawLine);
}

void CMockCanvas::FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor)
{
	m_data.push_back(Method::FillPolygon);
}

void CMockCanvas::DrawCircle(CPoint const& center, double radius, uint32_t lineColor)
{
	m_data.push_back(Method::DrawCircle);
}

void CMockCanvas::FillCircle(CPoint const& center, double radius, uint32_t fillColor)
{
	m_data.push_back(Method::FillCircle);
}

std::vector<CMockCanvas::Method> CMockCanvas::GetData() const
{
	return m_data;
}