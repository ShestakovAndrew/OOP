#include "catch.hpp"
#include "GeometricFigures/Rectangle.h"
#include "MockCanvas.h"

TEST_CASE("ÑRectangle constructor should be work correctló.")
{
	CPoint leftTop = { 0, 20 };
	double width = 10;
	double height = 20;
	uint32_t outlineColor = 0xff00ff;
	uint32_t fillColor = 0xffffff;

	CRectangle rectangle(leftTop, width, height, outlineColor, fillColor);

	REQUIRE(rectangle.GetLeftTop() == leftTop);
	REQUIRE(rectangle.GetWidth() == width);
	REQUIRE(rectangle.GetHeight() == height);
	REQUIRE(rectangle.GetOutlineColor() == outlineColor);
	REQUIRE(rectangle.GetFillColor() == fillColor);
}

TEST_CASE("Area, perimeter and right bottom of rectangle should be calculate correctly.")
{
	CRectangle triangle({ 0, 20 }, 10, 20, 0xff00ff, 0xffffff);

	REQUIRE(triangle.GetArea() == 200);
	REQUIRE(triangle.GetPerimeter() == 60);
	REQUIRE(triangle.GetRightBottom() == CPoint{10, 0});
}

TEST_CASE("ToString() should be return correct rectangle information.")
{
	CRectangle triangle({ 0, 20 }, 10, 20, 0xff00ff, 0xffffff);

	std::string info = "Type shape: Rectangle\nPerimeter: 60.00\nArea: 200.00\nLeft top point: [0.00, 20.00]\nRight bottom point: [10.00, 0.00]\nWidth: 10.00\nHeight: 20.00\nOutline color: #ff00ff\nFill color: #ffffff";
	REQUIRE(triangle.ToString() == info);
}

TEST_CASE("Draw in Rectangle must DrawPolygon on Canvas")
{
	CMockCanvas canvas;

	CPoint leftTop = { 5, 5.5 };
	double width = 10;
	double height = 5;
	CRectangle rectangle(leftTop, width, height, 0, 0xffffff);

	rectangle.Draw(canvas);
	std::vector<CMockCanvas::Method> reqData = { CMockCanvas::Method::DrawPolygon };
	CHECK(canvas.GetData() == reqData);
}