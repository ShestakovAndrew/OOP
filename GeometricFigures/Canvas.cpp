#include "Canvas.h"

namespace
{
	sf::Color GetRGBColor(uint32_t color)
	{
		uint32_t blue = color % 256;
		uint32_t green = (color / 256) % 256;
		uint32_t red = ((color / 256) / 256) % 256;

		return sf::Color(red, green, blue);
	}
}

CCanvas::CCanvas(sf::RenderTarget& renderTarget)
	: m_renderTarget(renderTarget)
{
	m_width = renderTarget.getSize().x;
	m_height = renderTarget.getSize().y;
}

void CCanvas::DrawLine(CPoint const& from, CPoint const& to, uint32_t lineColor)
{
	sf::Vertex line[] = 
	{
		sf::Vertex(GetCoordOnCanvas(from)),
		sf::Vertex(GetCoordOnCanvas(to))
	};
	line[0].color = GetRGBColor(lineColor);
	line[1].color = GetRGBColor(lineColor);
	m_renderTarget.draw(line, 2, sf::Lines);
}

void CCanvas::FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor)
{
	sf::ConvexShape shape;
	shape.setPointCount(points.size());

	for (size_t i = 0; i < points.size(); i++)
	{
		shape.setPoint(i, GetCoordOnCanvas(points[i]));
	}

	shape.setFillColor(GetRGBColor(fillColor));
	m_renderTarget.draw(shape);
}

void CCanvas::DrawCircle(CPoint const& center, double radius, uint32_t lineColor)
{
	sf::CircleShape circle = CreateCircleShape(center, radius);
	circle.setOutlineColor(GetRGBColor(lineColor));
	circle.setOutlineThickness(2.f);
	m_renderTarget.draw(circle);
}

void CCanvas::FillCircle(CPoint const& center, double radius, uint32_t fillColor)
{
	sf::CircleShape circle = CreateCircleShape(center, radius);
	circle.setFillColor(GetRGBColor(fillColor));
	m_renderTarget.draw(circle);
}

sf::Vector2f CCanvas::GetCoordOnCanvas(CPoint const& point)
{
	return sf::Vector2f((float)point.x, m_height - (float)point.y);
}

sf::CircleShape CCanvas::CreateCircleShape(CPoint const& center, double radius)
{
	sf::CircleShape circle((float)radius);
	circle.setOrigin((float)radius, (float)radius);
	circle.move(GetCoordOnCanvas(center));
	return circle;
}