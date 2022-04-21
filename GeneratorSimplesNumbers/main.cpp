#include "GeneratorSimplesNumbers.h"

int main(int argc, const char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		int uppedBound = GetUpperBound(argc, argv);

		std::set<size_t> primeNumbers = GeneratePrimeNumbersSet(uppedBound);

		DisplayPrimeNumbers(primeNumbers);
	}
	catch (std::invalid_argument const& err)
	{
		std::cerr << err.what() << std::endl;
		return 1;
	}
}