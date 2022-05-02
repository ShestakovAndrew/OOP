#include "ShapesController.h"
#include <iostream>
#include <string>

int main()
{
	CShapesController controller(std::cin, std::cout);

	std::string command;

	while (!std::cin.eof() and !std::cin.fail())
	{
		if (!controller.HandleCommand())
		{
			std::cout << "Unknown command!\n";
		}
	}

	controller.PrintShapeWithMaxArea();
	controller.PrintShapeWithMinPerimeter();

	return 0;
}