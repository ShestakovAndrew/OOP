#pragma once
#include "ICanvas.h"
#include "SFML/Graphics.hpp"

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderTarget& renderTarget);
	void DrawLine(CPoint const& from, CPoint const& to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint>const& points, uint32_t fillColor) override;
	void DrawCircle(CPoint const& center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint const& center, double radius, uint32_t fillColor) override;

private:
	sf::Vector2f GetCoordOnCanvas(CPoint const& point);
	sf::CircleShape CreateCircleShape(CPoint const& center, double radius);

	sf::RenderTarget& m_renderTarget;
	int m_width;
	int m_height;
};

