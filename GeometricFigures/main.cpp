#include "ShapesController.h"

int main()
{
	CShapesController controller(std::cin, std::cout);
	while (!std::cin.eof() and !std::cin.fail())
	{
		if (!controller.HandleCommand())
		{
			std::cout << "Unknown command!\n";
		}
	}
	controller.PrintShapeWithMaxArea();
	controller.PrintShapeWithMinPerimeter();
	controller.DrawShapes();
	return 0;
}