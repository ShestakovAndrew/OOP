#include "Canvas.h"

CCanvas::CCanvas(sf::RenderTarget& window)
	: m_window(window)
{
	m_width = window.getSize().x;
	m_height = window.getSize().y;
}

sf::Color GetRGBColor(uint32_t color)
{
	uint32_t blue = color % 256;
	uint32_t green = (color / 256) % 256;
	uint32_t red = ((color / 256) / 256) % 256;

	return sf::Color(red, green, blue);
}

sf::Vector2f CCanvas::GetCoordOnCanvas(CPoint point)
{
	return sf::Vector2f((float)point.x, m_height - (float)point.y);
}

void CCanvas::DrawLine(CPoint from, CPoint to, uint32_t lineColor)
{
	sf::Vertex line[] = {
		sf::Vertex(GetCoordOnCanvas(from)),
		sf::Vertex(GetCoordOnCanvas(to))
	};
	line[0].color = GetRGBColor(lineColor);
	line[1].color = GetRGBColor(lineColor);

	m_window.draw(line, 2, sf::Lines);
}

void CCanvas::DrawPolygon(std::vector<CPoint> points, uint32_t outlineColor, uint32_t fillColor)
{
	sf::ConvexShape shape;

	shape.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		shape.setPoint(i, GetCoordOnCanvas(points[i]));
	}

	shape.setFillColor(GetRGBColor(fillColor));
	shape.setOutlineColor(GetRGBColor(outlineColor));
	shape.setOutlineThickness(2.f);

	m_window.draw(shape);
}

void CCanvas::DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t fillColor)
{
	sf::CircleShape circle((float)radius);
	circle.setOrigin((float)radius, (float)radius);
	circle.move(GetCoordOnCanvas(center));

	circle.setOutlineColor(GetRGBColor(lineColor));
	circle.setOutlineThickness(2.f);
	circle.setFillColor(GetRGBColor(fillColor));

	m_window.draw(circle);
}