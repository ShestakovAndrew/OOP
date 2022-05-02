#include "ShapesController.h"

CShapesController::CShapesController(std::istream& input, std::ostream& output)
	: m_input(input), m_output(output)
	, m_actionMap(
	{ 
		{ "LineSegment", std::bind(&CShapesController::LineSegment, this, std::placeholders::_1) },
		{ "Rectangle", std::bind(&CShapesController::Rectangle, this, std::placeholders::_1) },
		{ "Triangle", std::bind(&CShapesController::Triangle, this, std::placeholders::_1) },
		{ "Circle", std::bind(&CShapesController::Circle, this, std::placeholders::_1) }
	})
{
}

bool CShapesController::HandleCommand()
{
    return false;
}

bool CShapesController::LineSegment(std::istream& command)
{
    return false;
}

bool CShapesController::Triangle(std::istream& command)
{
    return false;
}

bool CShapesController::Rectangle(std::istream& command)
{
    return false;
}

bool CShapesController::Circle(std::istream& command)
{
    return false;
}

void CShapesController::GetShapesInfo() const
{
}

void CShapesController::PrintShapeWithMaxArea() const
{
}

void CShapesController::PrintShapeWithMinPerimeter() const
{
}
