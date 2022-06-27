#include "catch.hpp"
#include "GeometricFigures/ShapesController.h"

void VerifyCommandHandling(std::string const& command, std::string const& expectedResult)
{
	std::stringstream input, output;
	CShapesController controller(input, output);
	input << command;
	REQUIRE(controller.HandleCommand());
	controller.GetShapeInfo();
	REQUIRE(expectedResult == output.str());
}

TEST_CASE("Invalid command should be return false.")
{
	std::stringstream input, output;
	CShapesController process(input, output);
	input << "invalid command!";
	REQUIRE(!process.HandleCommand());
}

TEST_CASE("Invalid shape data should be print invalid message.")
{
	std::string messageInvalid;

	SECTION("LineSegment")
	{
		messageInvalid = "Invalid input.\nUsage: LineSegment <start point> <end point> <outline color>\n";

		VerifyCommandHandling("LineSegment 1 2 3 4", messageInvalid);
		VerifyCommandHandling("LineSegment 1 2 3 ffffff", messageInvalid);
		VerifyCommandHandling("LineSegment 1 2 3 4 5 ffffff", messageInvalid);
		VerifyCommandHandling("LineSegment 1 2 3 4 ffffff ffffff", messageInvalid);
	}

	SECTION("Triangle")
	{
		messageInvalid = "Invalid input.\nUsage: Triangle <vertex1> <vertex2> <vertex3> <outline color> <fill color>\n";
		VerifyCommandHandling("Triangle 1 2 3 4 5 6 ffffff", messageInvalid);
		VerifyCommandHandling("Triangle 1 2 3 4 5 ffffff ffffff", messageInvalid);
		VerifyCommandHandling("Triangle 1 2 3 4 5 6", messageInvalid);
	}

	SECTION("Rectangle")
	{
		messageInvalid = "Invalid input.\nUsage: Rectangle <left top vertex> <width> <height> <outline color> <fill color>\n";
		VerifyCommandHandling("Rectangle 1 2 3 4 ffffff", messageInvalid);
		VerifyCommandHandling("Rectangle 1 2 3 4 5 ffffff ffffff", messageInvalid);
		VerifyCommandHandling("Rectangle 1 2 3 ffffff ffffff", messageInvalid);
		VerifyCommandHandling("Rectangle 1 2 3 4", messageInvalid);
	}

	SECTION("Circle")
	{
		messageInvalid = "Invalid input.\nUsage: Circle <center> <radius> <outline color> <fill color>\n";
		VerifyCommandHandling("Circle 1 2 ffffff ffffff", messageInvalid);
		VerifyCommandHandling("Circle 1 2 3 4 ffffff ffffff", messageInvalid);
		VerifyCommandHandling("Circle 1 2 3 ffffff", messageInvalid);
		VerifyCommandHandling("Circle 1 2 3", messageInvalid);
	}
}

TEST_CASE("Valid shape data should be add to vector shapes.")
{
	std::string shapesInfo;

	SECTION("LineSegment")
	{
		shapesInfo = "Type shape: Line Segment\nPerimeter: 20.62\nArea: 0.00\nStart point: [0.00, 0.00]\nEnd point: [5.00, 20.00]\nOutline color: ff00ff";
		VerifyCommandHandling("LineSegment 0 0 5 20 ff00ff", shapesInfo);
	}

	SECTION("Triangle")
	{
		shapesInfo = "Type shape: Triangle\nPerimeter: 41.22\nArea: 39.00\nVertex1: [1.00, 1.00]\nVertex2: [3.00, 5.00]\nVertex3: [20.00, 0.00]\nOutline color: ff00ff\nFill color: ffffff";
		VerifyCommandHandling("Triangle 1 1 3 5 20 0 ff00ff ffffff", shapesInfo);
	}

	SECTION("Rectangle")
	{
		shapesInfo = "Type shape: Rectangle\nPerimeter: 60.00\nArea: 200.00\nLeft top point: [0.00, 20.00]\nRight bottom point: [10.00, 0.00]\nWidth: 10.00\nHeight: 20.00\nOutline color: ff00ff\nFill color: ffffff";
		VerifyCommandHandling("Rectangle 0 20 10 20 ff00ff ffffff", shapesInfo);
	}

	SECTION("Circle")
	{
		shapesInfo = "Type shape: Circle\nPerimeter: 94.25\nArea: 706.86\nCenter: [0.00, 0.00]\nRadius: 15.00\nOutline color: ff00ff\nFill color: ffffff";
		VerifyCommandHandling("Circle 0 0 15 ff00ff ffffff", shapesInfo);
	}
}

TEST_CASE("If shapes empty should be print about it.")
{
	std::stringstream input, output;
	CShapesController controller(input, output);
	std::string messageInvalid = "List of shapes is empty.\n";

	SECTION("PrintShapeWithMinPerimeter")
	{
		controller.PrintShapeWithMinPerimeter();
		REQUIRE(output.str() == messageInvalid);
	}

	SECTION("PrintShapeWithMaxArea")
	{
		controller.PrintShapeWithMaxArea();
		REQUIRE(output.str() == messageInvalid);
	}
}

TEST_CASE("PrintShapeWithMaxArea() should be print shape with max area.")
{
	std::stringstream input, output;
	CShapesController controller(input, output);

	input << "Circle 0 0 12 ffffff ffffff" << std::endl
		  << "Circle 0 0 11 ffffff ffffff" << std::endl
		  << "Circle 0 0 10 ffffff ffffff";

	while (!input.eof()) controller.HandleCommand();

	controller.PrintShapeWithMaxArea();
	std::string shapeInfo = "Shape with max area:\nType shape: Circle\nPerimeter: 75.40\nArea: 452.39\nCenter: [0.00, 0.00]\nRadius: 12.00\nOutline color: ffffff\nFill color: ffffff";
	REQUIRE(output.str() == shapeInfo);
}

TEST_CASE("PrintShapeWithMinPerimeter() should be print shape with min perimeter.")
{
	std::stringstream input, output;
	CShapesController controller(input, output);

	input << "Rectangle 0 20 22 10 ffffff ffffff" << std::endl
		  << "Rectangle 0 20 21 10 ffffff ffffff" << std::endl
		  << "Rectangle 0 20 20 10 ffffff ffffff" << std::endl;

	while (!input.eof()) controller.HandleCommand();

	controller.PrintShapeWithMinPerimeter();
	std::string shapeInfo = "Shape with min perimeter:\nType shape: Rectangle\nPerimeter: 60.00\nArea: 200.00\nLeft top point: [0.00, 20.00]\nRight bottom point: [20.00, 10.00]\nWidth: 20.00\nHeight: 10.00\nOutline color: ffffff\nFill color: ffffff";
	REQUIRE(output.str() == shapeInfo);
}