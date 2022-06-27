#pragma once
#include <functional>
#include <optional>
#include <sstream>
#include <map>
#include <vector>
#include <memory>
#include <regex>
#include <iostream>
#include <string>

#include "LineSegment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Canvas.h"

//можно разделить этот контроллер. ¬ынести создание в отдельный класс (Factory)

class CShapesController
{
public:
	CShapesController(std::istream& input, std::ostream& output);
	bool HandleCommand();

	void GetShapeInfo() const;
	void PrintShapeWithMaxArea() const;
	void PrintShapeWithMinPerimeter() const;

private:
	using Handler = std::function<void(std::istream& command)>;
	using ActionMap = std::map<std::string, Handler>;

	void LineSegment(std::istream& command);
	void Triangle(std::istream& command);
	void Rectangle(std::istream& command);
	void Circle(std::istream& command);
	void DrawShapes();

	const ActionMap m_actionMap;
	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

