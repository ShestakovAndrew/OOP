#include "catch.hpp"
#include "GeometricFigures/Triangle.h"

TEST_CASE("ÑTriangle constructor should work correctló.")
{
	CPoint vertex1 = { 1, 1 };
	CPoint vertex2 = { 3, 5 };
	CPoint vertex3 = { 20, 0 };
	uint32_t outlineColor = 0xff00ff;
	uint32_t fillColor = 0xffffff;

	CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

	REQUIRE(triangle.GetVertex1() == vertex1);
	REQUIRE(triangle.GetVertex2() == vertex2);
	REQUIRE(triangle.GetVertex3() == vertex3);
	REQUIRE(triangle.GetOutlineColor() == outlineColor);
	REQUIRE(triangle.GetFillColor() == fillColor);
}

TEST_CASE("Area and perimeter of triangle should be calculate correctly.")
{
	CTriangle triangle({ 1, 1 }, { 3, 5 }, { 20, 0 }, 0xff00ff, 0xffffff);

	REQUIRE(triangle.GetArea() == 39);
	REQUIRE(round(triangle.GetPerimeter() * 100) / 100 == 41.22);
}

TEST_CASE("ToString() must return triangle information")
{
	CTriangle triangle({ 1, 1 }, { 3, 5 }, { 20, 0 }, 0xff00ff, 0xffffff);

	std::string info = "Type shape: Triangle\nPerimeter: 41.22\nArea: 39.00\nVertex1: [1.00, 1.00]\nVertex2: [3.00, 5.00]\nVertex3: [20.00, 0.00]\nOutline color: #ff00ff\nFill color: #ffffff";
	REQUIRE(triangle.ToString() == info);
}