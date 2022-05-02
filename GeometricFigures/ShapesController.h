#pragma once
#include <functional>
#include <map>
#include <vector>
#include <memory>

#include "LineSegment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

class CShapesController
{
public:
	CShapesController(std::istream& input, std::ostream& output);
	bool HandleCommand();

	void PrintShapeWithMaxArea() const;
	void PrintShapeWithMinPerimeter() const;

private:
	using Handler = std::function<bool(std::istream& command)>;
	using ActionMap = std::map<std::string, Handler>;

	bool LineSegment(std::istream& command);
	bool Triangle(std::istream& command);
	bool Rectangle(std::istream& command);
	bool Circle(std::istream& command);
	void GetShapesInfo() const;

	const ActionMap m_actionMap;
	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

