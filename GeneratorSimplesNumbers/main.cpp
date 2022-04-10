#include "GeneratorSimplesNumbers.h"

int main(int argc, const char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		uint64_t uppedBound = GetUpperBound(argc, argv);

		std::set<uint64_t> primeNumbers = GeneratePrimeNumbersSet(uppedBound);

		DisplayPrimeNumbers(primeNumbers);
	}
	catch (std::invalid_argument const& err)
	{
		std::cerr << err.what() << std::endl;
		return 1;
	}
}