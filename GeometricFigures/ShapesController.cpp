#include "ShapesController.h"

#include <regex>

namespace
{
	const std::string REGEX_PARSE_COMMAND = R"(^(LineSegment|Rectangle|Triangle|Circle) ([\d\.]+) ([\d\.]+) ([\d\.]+) ([\d\.]+)? ?([\d\.]+)? ?([\d\.]+)? ?(#[0-9a-f]{6}) ?(#[0-9a-f]{6})?$)";

	bool ParseCommand(std::string commandFromUser, Arguments& arguments)
	{
		std::regex regex(REGEX_PARSE_COMMAND, std::regex_constants::icase);
		std::smatch match;

		if (!std::regex_match(commandFromUser, match, regex)) return false;

		arguments.shape = std::string(match[1]);

		if (!arguments.shape.has_value()) return false;

		arguments.firstNumber = std::stod(match[2].str());
		arguments.secondNumber = std::stod(std::string(match[3]));
		arguments.thirdNumber = std::stod(std::string(match[4]));
		arguments.fourthNumber = std::stod(std::string(match[5]));
		arguments.fifthNumber = std::stod(std::string(match[6]));
		arguments.sixthNumber = std::stod(std::string(match[7]));

		arguments.outlineColor = std::stoul(match[8].str(), 0, 16);
		arguments.fillColor = std::stoul(match[9].str(), 0, 16);

		return true;
	}
}

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
	std::string commandFromUser;
	std::getline(m_input, commandFromUser);

	Arguments args;
	if (!ParseCommand(commandFromUser, args)) return false;

	if (auto const& it = m_actionMap.find(args.shape.value()); it != m_actionMap.end())
	{
		return it->second(args);
	}

	return false;
}

bool CShapesController::LineSegment(Arguments const& args)
{
	if (not args.firstNumber.has_value() or
		not args.secondNumber.has_value() or
		not args.thirdNumber.has_value() or
		not args.fourthNumber.has_value() or
		args.fifthNumber.has_value() or
		args.sixthNumber.has_value() or
		not args.outlineColor.has_value() or
		args.fillColor.has_value()
	)
	{
		m_output << "Invalid input" << std::endl 
			<< "Usage: LineSegment <start point> <end point> <outline color>" << std::endl
			<< "Example: LineSegment 10.3 20.15 30.7 40.4 #ff0000" << std::endl;
		return false;
	}

	CPoint startPoint = { args.firstNumber.value(), args.secondNumber.value() };
	CPoint endPoint = { args.thirdNumber.value(), args.fourthNumber.value() };
	uint32_t outlineColor = args.outlineColor.value();

	m_shapes.push_back(
		std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor)
	);

	return true;
}

bool CShapesController::Triangle(Arguments const& args)
{
	if (not args.firstNumber.has_value() or
		not args.secondNumber.has_value() or
		not args.thirdNumber.has_value() or
		not args.fourthNumber.has_value() or
		not args.fifthNumber.has_value() or
		not args.sixthNumber.has_value() or
		not args.outlineColor.has_value() or
		not args.fillColor.has_value()
		)
	{
		m_output << "Invalid input" << std::endl 
			<< "Usage: Triangle <vertex1> <vertex2> <vertex3> <outline color> <fill color>" << std::endl
			<< "Example: Triangle 0 3.1 3.5 5.1 0 0 #ff0000 #00ff00" << std::endl;
		return false;
	}

	CPoint vertex1 = { args.firstNumber.value(), args.secondNumber.value() };
	CPoint vertex2 = { args.thirdNumber.value(), args.fourthNumber.value() };
	CPoint vertex3 = { args.fifthNumber.value(), args.sixthNumber.value() };
	uint32_t outlineColor = args.outlineColor.value();
	uint32_t fillColor = args.fillColor.value();

	m_shapes.push_back(
		std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor)
	);
	
	return true;
}

bool CShapesController::Rectangle(Arguments const& args)
{
	if (not args.firstNumber.has_value() or
		not args.secondNumber.has_value() or
		not args.thirdNumber.has_value() or
		not args.fourthNumber.has_value() or
		args.fifthNumber.has_value() or
		args.sixthNumber.has_value() or
		not args.outlineColor.has_value() or
		not args.fillColor.has_value()
		)
	{
		m_output << "Invalid input" << std::endl
			<< "Usage: Rectangle <left top vertex> <width> <height> <outline color> <fill color>" << std::endl
			<< "Example: Rectangle 5 3.2 4 5.2 #ff0000 #00ff00" << std::endl;
		return false;
	}

	CPoint leftTop = { args.firstNumber.value(), args.secondNumber.value() };
	double width = args.thirdNumber.value();
	double height = args.fourthNumber.value();
	uint32_t outlineColor = args.outlineColor.value();
	uint32_t fillColor = args.fillColor.value();

	m_shapes.push_back(
		std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor)
	);

	return true;
}

bool CShapesController::Circle(Arguments const& args)
{
	if (not args.firstNumber.has_value() or
		not args.secondNumber.has_value() or
		not args.thirdNumber.has_value() or
		args.fourthNumber.has_value() or
		args.fifthNumber.has_value() or
		args.sixthNumber.has_value() or
		not args.outlineColor.has_value() or
		not args.fillColor.has_value()
		)
	{
		m_output << "Invalid input" << std::endl 
			<< "Usage: Circle <center> <radius> <outline color> <fill color>" << std::endl
			<< "Example: Circle 0 3.1 5.1 #ff0000 #00ff00" << std::endl;
		return false;
	}

	CPoint center = { args.firstNumber.value(), args.secondNumber.value() };
	double radius = args.thirdNumber.value();
	uint32_t outlineColor = args.outlineColor.value();
	uint32_t fillColor = args.fillColor.value();

	m_shapes.push_back(
		std::make_shared<CCircle>(center, radius, outlineColor, fillColor)
	);

	return true;
}

void CShapesController::PrintShapeWithMaxArea() const
{
	if (m_shapes.empty())
	{
		m_output << "List of shapes is empty." << std::endl;
		return;
	}

	auto shapeWithMaxArea = std::max_element(m_shapes.begin(), m_shapes.end(), 
		[](const auto& shape1, const auto& shape2) 
		{
			return shape1->GetArea() < shape2->GetArea();
		}
	);

	m_output << "Shape with max area: " << std::endl
		<< (*shapeWithMaxArea)->ToString() << std::endl;
}

void CShapesController::PrintShapeWithMinPerimeter() const
{
	if (m_shapes.empty())
	{
		m_output << "List of shapes is empty." << std::endl;
		return;
	}

	auto shapeWithMinPerimeter = std::min_element(m_shapes.begin(), m_shapes.end(), 
		[](const auto& shape1, const auto& shape2) 
		{
			return shape1->GetPerimeter() < shape2->GetPerimeter();
		}
	);

	m_output << "Shape with max area: " << std::endl 
		<< (*shapeWithMinPerimeter)->ToString() << std::endl;
}
