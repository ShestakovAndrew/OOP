#include "Rectangle.h"

CRectangle::CRectangle(CPoint leftTop, CPoint rightBottom, double width, double height, uint32_t outlineColor, uint32_t fillColor)
	: m_leftTop(leftTop), m_width(width), m_height(height), m_outlineColor(outlineColor), m_fillColor(fillColor)
{
}

std::string CRectangle::ToString() const
{
	std::stringstream sstream;

	sstream << std::fixed << std::setprecision(2)
		<< "Type shape: Circle" << std::endl
		<< "Perimeter: " << GetPerimeter() << std::endl
		<< "Area: " << GetArea() << std::endl
		<< "Left top point: " << m_leftTop.ToString() << std::endl
		<< "Right bottom point: " << GetRightBottom().ToString() << std::endl
		<< "Width: " << GetWidth() << std::endl
		<< "Height: " << GetHeight() << std::endl
		<< "Outline color: #" << std::hex << std::setw(6) << std::setfill('0') << m_outlineColor
		<< "Fill color: #" << std::hex << std::setw(6) << std::setfill('0') << m_fillColor;

	return sstream.str();
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (m_width + m_height);
}

uint32_t CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

uint32_t CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	return { m_leftTop.x + m_width, m_leftTop.y - m_height };
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}
