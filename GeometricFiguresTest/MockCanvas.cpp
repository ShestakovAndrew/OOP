#include "MockCanvas.h"

void CMockCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	m_data.push_back(Method::DrawLine);
}

void CMockCanvas::DrawPolygon(std::vector<CPoint> points, uint32_t outlineColor, uint32_t fillColor)
{
	m_data.push_back(Method::DrawPolygon);
}

void CMockCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t fillColor)
{
	m_data.push_back(Method::DrawCircle);
}

std::vector<CMockCanvas::Method> CMockCanvas::GetData() const
{
	return m_data;
}