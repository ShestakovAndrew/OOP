#pragma once
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderTarget& window);
	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void DrawPolygon(std::vector<CPoint> points, uint32_t outlineColor, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t fillColor) override;

private:
	sf::Vector2f GetCoordOnCanvas(CPoint point);

	sf::RenderTarget& m_window;
	int m_width;
	int m_height;
};

