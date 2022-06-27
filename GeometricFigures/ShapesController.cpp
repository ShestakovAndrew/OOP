#include "ShapesController.h"

namespace
{
	bool IsNumber(std::string const& str)
	{
		for (auto symbol : str)
		{
			if (!std::isdigit(symbol) && symbol != '.')
			{
				return false;
			}
		}
		return true;
	}
	bool IsColor(std::string const& str)
	{
		if (str.size() != 6) return false;

		for (auto symbol : str)
		{
			if (!std::isdigit(symbol) && (symbol < 'a' || symbol > 'f') && (symbol < 'A' || symbol > 'F'))
			{
				return false;
			}
		}
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
		{ "Circle", std::bind(&CShapesController::Circle, this, std::placeholders::_1) },
		{ "Draw", std::bind(&CShapesController::DrawShapes, this) }
	})
{
}

bool CShapesController::HandleCommand()
{
	std::string commandFromUser;
	std::getline(m_input, commandFromUser);
	std::istringstream iss(commandFromUser);

	std::string shapeType;
	iss >> shapeType;

	if (auto it = m_actionMap.find(shapeType); it != m_actionMap.end())
	{
		it->second(iss);
		return true;
	}

	return false;
}

void CShapesController::LineSegment(std::istream& command)
{
	std::string startPointX, startPointY, endPointX, endPointY;
	std::string outlineColorStr;

	if (((command >> startPointX) && IsNumber(startPointX)) &&
		((command >> startPointY) && IsNumber(startPointY)) &&
		((command >> endPointX) && IsNumber(endPointX)) &&
		((command >> endPointY) && IsNumber(endPointY)) &&
		((command >> outlineColorStr) && IsColor(outlineColorStr)) && command.eof())
	{
		CPoint startPoint = { std::stod(startPointX), std::stod(startPointY) };
		CPoint endPoint = { std::stod(endPointX), std::stod(endPointY) };
		uint32_t outlineColor = std::stoul(outlineColorStr, 0, 16);

		m_shapes.push_back(
			std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor)
		);
	}
	else
	{
		m_output << "Invalid input." << std::endl
			<< "Usage: LineSegment <start point> <end point> <outline color>" << std::endl;
	}
}

void CShapesController::Triangle(std::istream& command)
{
	std::string vertex1x, vertex1y, vertex2x, vertex2y, vertex3x, vertex3y;
	std::string outlineColorStr, fillColorStr;

	if (((command >> vertex1x) && IsNumber(vertex1x)) &&
		((command >> vertex1y) && IsNumber(vertex1y)) &&
		((command >> vertex2x) && IsNumber(vertex2x)) &&
		((command >> vertex2y) && IsNumber(vertex2y)) &&
		((command >> vertex3x) && IsNumber(vertex3x)) &&
		((command >> vertex3y) && IsNumber(vertex3y)) &&
		((command >> outlineColorStr) && IsColor(outlineColorStr)) &&
		((command >> fillColorStr) && IsColor(fillColorStr)) && command.eof())
	{
		CPoint vertex1 = { std::stod(vertex1x), std::stod(vertex1y) };
		CPoint vertex2 = { std::stod(vertex2x), std::stod(vertex2y) };
		CPoint vertex3 = { std::stod(vertex3x), std::stod(vertex3y) };
		uint32_t outlineColor = std::stoul(outlineColorStr, 0, 16);
		uint32_t fillColor = std::stoul(fillColorStr, 0, 16);

		m_shapes.push_back(
			std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor)
		);
	}
	else
	{
		m_output << "Invalid input." << std::endl
			<< "Usage: Triangle <vertex1> <vertex2> <vertex3> <outline color> <fill color>" << std::endl;
	}
}

void CShapesController::Rectangle(std::istream& command)
{
	std::string leftTopX, leftTopY, widthStr, heightStr;
	std::string outlineColorStr, fillColorStr;

	if (((command >> leftTopX) && IsNumber(leftTopX)) &&
		((command >> leftTopY) && IsNumber(leftTopY)) &&
		((command >> widthStr) && IsNumber(widthStr)) &&
		((command >> heightStr) && IsNumber(heightStr)) &&
		((command >> outlineColorStr) && IsColor(outlineColorStr)) &&
		((command >> fillColorStr) && IsColor(fillColorStr)) && command.eof())
	{
		CPoint leftTop = { std::stod(leftTopX), std::stod(leftTopY) };
		double width = std::stod(widthStr);
		double height = std::stod(heightStr);
		uint32_t outlineColor = std::stoul(outlineColorStr, 0, 16);
		uint32_t fillColor = std::stoul(fillColorStr, 0, 16);

		m_shapes.push_back(
			std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor)
		);
	}
	else
	{
		m_output << "Invalid input." << std::endl
			<< "Usage: Rectangle <left top vertex> <width> <height> <outline color> <fill color>" << std::endl;
	}
}

void CShapesController::Circle(std::istream& command)
{
	std::string centerX, centerY, radiusStr;
	std::string outlineColorStr, fillColorStr;

	if (((command >> centerX) && IsNumber(centerX)) &&
		((command >> centerY) && IsNumber(centerY)) &&
		((command >> radiusStr) && IsNumber(radiusStr)) &&
		((command >> outlineColorStr) && IsColor(outlineColorStr)) &&
		((command >> fillColorStr) && IsColor(fillColorStr)) && command.eof())
	{
		CPoint center = { std::stod(centerX), std::stod(centerY) };
		double radius = std::stod(radiusStr);
		uint32_t outlineColor = std::stoul(outlineColorStr, 0, 16);
		uint32_t fillColor = std::stoul(fillColorStr, 0, 16);

		m_shapes.push_back(
			std::make_shared<CCircle>(center, radius, outlineColor, fillColor)
		);
	}
	else
	{
		m_output << "Invalid input." << std::endl
			<< "Usage: Circle <center> <radius> <outline color> <fill color>" << std::endl;
	}
}

void CShapesController::DrawShapes()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(800, 800), "Shapes", sf::Style::Default, settings);
	CCanvas canvas(window);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear(sf::Color(255, 255, 255));
		for (auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
		window.display();
	}
}

void CShapesController::GetShapeInfo() const
{
	for (auto const& shape : m_shapes)
	{
		m_output << shape->ToString();
	}
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

	m_output << "Shape with max area:" << std::endl
		<< (*shapeWithMaxArea)->ToString();
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

	m_output << "Shape with min perimeter:" << std::endl 
		<< (*shapeWithMinPerimeter)->ToString();
}
