#include "Vector.h"

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		std::vector<double> sequence;
		SetRealNumbersTo(sequence);
		AddMeanPositiveNumberForAllElementsIn(sequence);
		PrintRealNumbers(sequence);
	}
	catch (const std::bad_cast& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}