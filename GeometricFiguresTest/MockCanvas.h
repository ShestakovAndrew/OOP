#pragma once
#include "../GeometricFigures/ICanvas.h"

class CMockCanvas : public ICanvas
{
public:
	enum class Method
	{
		DrawLine,
		DrawPolygon,
		DrawCircle
	};

	void DrawLine(CPoint from, CPoint to, uint32_t lineColor) override;
	void DrawPolygon(std::vector<CPoint> points, uint32_t outlineColor, uint32_t fillColor) override;
	void DrawCircle(CPoint center, double radius, uint32_t lineColor, uint32_t fillColor) override;

	std::vector<Method> GetData() const;

private:
	std::vector<Method> m_data;
};

