#include "ShapesController.h"

namespace
{
	std::vector<std::string> ParseCommand(std::istream& command)
	{
		std::vector<std::string> result;
		std::string param;

		while (!command.eof() && !command.fail())
		{
			command >> param;
			result.push_back(param);
		}
		return result;
	}

	bool IsNumbers(
		std::vector<std::string>::const_iterator begin,
		std::vector<std::string>::const_iterator end
	)
	{
		for (auto& number = begin; number != end; number++)
		{
			for (auto symbol : *number)
			{
				if (!std::isdigit(symbol) && symbol != '.')
				{
					return false;
				}
			}
		}
		return true;
	}

	bool IsColors(
		std::vector<std::string>::const_iterator begin,
		std::vector<std::string>::const_iterator end
	)
	{
		for (auto color = begin; color != end; color++)
		{
			for (auto symbol : *color)
			{
				if (!std::isdigit(symbol) && (symbol < 'a' || symbol > 'f') && (symbol < 'A' || symbol > 'F'))
				{
					return false;
				}
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
	std::vector<std::string> splitCommand = ParseCommand(command);
	if (splitCommand.size() == 5
		&& IsNumbers(splitCommand.begin() + 0, splitCommand.begin() + 4)
		&& IsColors(splitCommand.begin() + 4, splitCommand.begin() + 5)
	)
	{
		CPoint startPoint = { std::stod(splitCommand[0]), std::stod(splitCommand[1]) };
		CPoint endPoint = { std::stod(splitCommand[2]), std::stod(splitCommand[3]) };
		uint32_t outlineColor = std::stoul(splitCommand[4], 0, 16);

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
	std::vector<std::string> splitCommand = ParseCommand(command);
	if (splitCommand.size() == 8
		&& IsNumbers(splitCommand.begin() + 0, splitCommand.begin() + 6)
		&& IsColors(splitCommand.begin() + 6, splitCommand.begin() + 8)
	)
	{
		CPoint vertex1 = { std::stod(splitCommand[0]), std::stod(splitCommand[1]) };
		CPoint vertex2 = { std::stod(splitCommand[2]), std::stod(splitCommand[3]) };
		CPoint vertex3 = { std::stod(splitCommand[4]), std::stod(splitCommand[5]) };
		uint32_t outlineColor = std::stoul(splitCommand[6], 0, 16);
		uint32_t fillColor = std::stoul(splitCommand[7], 0, 16);

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
	std::vector<std::string> splitCommand = ParseCommand(command);
	if (splitCommand.size() == 6
		&& IsNumbers(splitCommand.begin() + 0, splitCommand.begin() + 4)
		&& IsColors(splitCommand.begin() + 4, splitCommand.begin() + 6)
	)
	{
		CPoint leftTop = { std::stod(splitCommand[0]), std::stod(splitCommand[1]) };
		double width = std::stod(splitCommand[2]);
		double height = std::stod(splitCommand[3]);
		uint32_t outlineColor = std::stoul(splitCommand[4], 0, 16);
		uint32_t fillColor = std::stoul(splitCommand[5], 0, 16);

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
	std::vector<std::string> splitCommand = ParseCommand(command);
	if (splitCommand.size() == 5
		&& IsNumbers(splitCommand.begin() + 0, splitCommand.begin() + 3)
		&& IsColors(splitCommand.begin() + 3, splitCommand.begin() + 5)
		)
	{
		CPoint center = { std::stod(splitCommand[0]), std::stod(splitCommand[1]) };
		double radius = std::stod(splitCommand[2]);
		uint32_t outlineColor = std::stoul(splitCommand[3], 0, 16);
		uint32_t fillColor = std::stoul(splitCommand[4], 0, 16);

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

void CShapesController::GetLastShapeInfo() const
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
