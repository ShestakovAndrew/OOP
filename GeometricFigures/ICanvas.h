#pragma once
#include <vector>

#include "Point.h"

class ICanvas
{
public:
	virtual ~ICanvas() {}
	virtual void DrawLine(CPoint const& from, CPoint const& to, uint32_t lineColor) = 0;
	virtual void FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor) = 0;
	virtual void DrawCircle(CPoint const& center, double radius, uint32_t lineColor) = 0;
	virtual void FillCircle(CPoint const& center, double radius, uint32_t fillColor) = 0;
};