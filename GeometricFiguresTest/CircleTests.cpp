#include "catch.hpp"
#include "GeometricFigures/Circle.h"
#include "MockCanvas.h"

TEST_CASE("ÑCircle constructor should be work correctló.")
{
	CPoint center = { 0, 0 };
	double radius = 15;
	uint32_t outlineColor = 0xff00ff;
	uint32_t fillColor = 0xffffff;

	CCircle circle(center, radius, outlineColor, fillColor);

	REQUIRE(circle.GetCenter() == center);
	REQUIRE(circle.GetRadius() == radius);
	REQUIRE(circle.GetOutlineColor() == outlineColor);
	REQUIRE(circle.GetFillColor() == fillColor);
}

TEST_CASE("Area, perimeter of circle should be calculate correctly.")
{
	CCircle circle({ 0, 0 }, 15, 0xff00ff, 0xffffff);

	REQUIRE(round(circle.GetArea() * 100) / 100 == 706.86);
	REQUIRE(round(circle.GetPerimeter() * 100) / 100 == 94.25);
}

TEST_CASE("ToString() should be return correct circle information.")
{
	CCircle circle({ 0, 0 }, 15, 0xff00ff, 0xffffff);

	std::string info = "Type shape: Circle\nPerimeter: 94.25\nArea: 706.86\nCenter: [0.00, 0.00]\nRadius: 15.00\nOutline color: #ff00ff\nFill color: #ffffff";
	REQUIRE(circle.ToString() == info);
}

TEST_CASE("Draw in Circle must DrawCircle on Canvas")
{
	CMockCanvas canvas;

	CPoint center = { 5, 0 };
	double radius = 10;
	CCircle circle(center, radius, 0, 0xffffff);

	circle.Draw(canvas);
	std::vector<CMockCanvas::Method> reqData = { CMockCanvas::Method::DrawCircle };
	CHECK(canvas.GetData() == reqData);
}