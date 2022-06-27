#pragma once
#include "GeometricFigures/ICanvas.h"

class CMockCanvas : public ICanvas
{
public:
	enum class Method
	{
		DrawLine,
		FillPolygon,
		DrawCircle,
		FillCircle
	};

	void DrawLine(CPoint const& from, CPoint const& to, uint32_t lineColor) override;
	void FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor) override;
	void DrawCircle(CPoint const& center, double radius, uint32_t lineColor) override;
	void FillCircle(CPoint const& center, double radius, uint32_t fillColor) override;

	std::vector<Method> GetData() const;

private:
	std::vector<Method> m_data;
};

