#include "Driver.h"
#include "Car.h"

int main()
{
	CCar vaz_2109;
	CDriver driver(vaz_2109, std::cin, std::cout);

	while (!std::cin.eof() and !std::cin.fail())
	{
		if (!driver.HandleCommand())
		{
			if (std::cin.eof()) return 0;

			std::cout << "Unknown command." << std::endl;
		}
	}

	return 0;
}


