#pragma once
#include <functional>
#include <optional>
#include <sstream>
#include <map>
#include <vector>
#include <memory>

#include "LineSegment.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

namespace
{
	struct Arguments
	{
		std::optional<std::string> shape;
		std::optional<double> firstNumber;
		std::optional<double> secondNumber;
		std::optional<double> thirdNumber;
		std::optional<double> fourthNumber;
		std::optional<double> fifthNumber;
		std::optional<double> sixthNumber;
		std::optional<uint32_t> outlineColor;
		std::optional<uint32_t> fillColor;
	};
}

class CShapesController
{
public:
	CShapesController(std::istream& input, std::ostream& output);
	bool HandleCommand();

	void GetLastShapeInfo() const;
	void PrintShapeWithMaxArea() const;
	void PrintShapeWithMinPerimeter() const;

private:
	using Handler = std::function<void(Arguments const& command)>;
	using ActionMap = std::map<std::string, Handler>;

	void LineSegment(Arguments const& command);
	void Triangle(Arguments const& command);
	void Rectangle(Arguments const& command);
	void Circle(Arguments const& command);

	const ActionMap m_actionMap;
	std::istream& m_input;
	std::ostream& m_output;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};

