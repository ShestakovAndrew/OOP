#include "Rectangle.h"

CRectangle::CRectangle(CPoint leftTop, CPoint rightBottom, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop), m_rightBottom(rightBottom), m_width(width), m_height(height), m_outlineColor(outlineColor), m_fillColor(fillColor)
{
}

double CRectangle::GetArea() const
{
	return 0.0;
}

double CRectangle::GetPerimeter() const
{
	return 0.0;
}

std::string CRectangle::ToString() const
{
	return std::string();
}

uint32_t CRectangle::GetOutlineColor() const
{
	return uint32_t();
}

uint32_t CRectangle::GetFillColor() const
{
	return uint32_t();
}

CPoint CRectangle::GetLeftTop() const
{
	return CPoint();
}

CPoint CRectangle::GetRightBottom() const
{
	return CPoint();
}

double CRectangle::GetWidth() const
{
	return 0.0;
}

double CRectangle::GetHeight() const
{
	return 0.0;
}
