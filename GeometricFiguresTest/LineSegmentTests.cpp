#include "catch.hpp"
#include "GeometricFigures/LineSegment.h"
#include "MockCanvas.h"

TEST_CASE("ÑLineSegment constructor should be work correctló.")
{
	CPoint startPoint = { 0, 0 };
	CPoint endPoint = { -5, 15 };
	uint32_t outlineColor = 0xff00ff;

	CLineSegment lineSegment(startPoint, endPoint, outlineColor);

	REQUIRE(lineSegment.GetStartPoint() == startPoint);
	REQUIRE(lineSegment.GetEndPoint() == endPoint);
	REQUIRE(lineSegment.GetOutlineColor() == outlineColor);
}

TEST_CASE("Area, perimeter of line segment should be calculate correctly.")
{
	CLineSegment lineSegment({ 0, 0 }, { -5, 15 }, 0xff00ff);

	REQUIRE(lineSegment.GetArea() == 0);
	REQUIRE(round(lineSegment.GetPerimeter() * 100) / 100 == 15.81);
}

TEST_CASE("ToString() should be return correct line segment information.")
{
	CLineSegment lineSegment({ 0, 0 }, { -5, 15 }, 0xff00ff);

	std::string info = "Type shape: Line Segment\nPerimeter: 15.81\nArea: 0.00\nStart point: [0.00, 0.00]\nEnd point: [-5.00, 15.00]\nOutline color: ff00ff";
	REQUIRE(lineSegment.ToString() == info);
}

TEST_CASE("Draw in LineSegment must DrawLine on Canvas")
{
	CMockCanvas canvas;
	CLineSegment line({ 0, 0 }, { 5, 12 }, 0xff00ff);

	line.Draw(canvas);
	std::vector<CMockCanvas::Method> reqData = { CMockCanvas::Method::DrawLine };
	REQUIRE(canvas.GetData() == reqData);
}