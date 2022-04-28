#include "Calculator.h"
#include "CalculatorController.h"

int main()
{
	CCalculator calc;
	CCalculatorController calcController(calc, std::cin, std::cout);

	while (!std::cin.eof() and !std::cin.fail())
	{
		if (!calcController.HandleCommand())
		{
			if (std::cin.eof()) return 0;

			std::cout << "Unknown command." << std::endl;
		}
	}

	return 0;
}