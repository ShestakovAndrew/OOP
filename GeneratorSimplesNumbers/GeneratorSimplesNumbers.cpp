#include "GeneratorSimplesNumbers.h"

namespace
{
	static const size_t MAX_RANGE = 100'000'000;
}

std::set<uint64_t> GeneratePrimeNumbersSet(size_t const& upperBound)
{
	std::set<uint64_t> primeNumbers;

	if (upperBound < 2) return primeNumbers;

	std::vector<bool> primes(upperBound + 1, true);
	primes[0] = false;

	for (size_t i = 2; i * i <= upperBound; ++i)
	{
		if (primes[i])
		{
			for (size_t j = i * i; j <= upperBound; j += 2 * i)
			{
				primes[j] = false;
			}
		}
	}

	for (size_t i = 1; i <= upperBound; i += 2)
	{
		if (primes[i]) primeNumbers.insert(i);
	}
	return primeNumbers;
}

void CheckArguments(int argc, const char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("arguments count invalid.");
	}

	std::string upperBoundStr = argv[1];

	if (!std::all_of(upperBoundStr.begin(), upperBoundStr.end(), std::isdigit))
	{
		throw std::invalid_argument("parametr is not a number.");
	}
}

void DisplayPrimeNumbers(std::set<uint64_t> const& primeNumbers)
{
	for (auto it = primeNumbers.cbegin(); it != primeNumbers.cend(); ++it)
	{
		std::cout << *it << ' ';
	}
}

uint64_t GetUpperBound(int argc, const char* argv[])
{
	CheckArguments(argc, argv);

	uint64_t upperBound = std::stoi(argv[1]);

	if (!upperBound) throw std::invalid_argument("Invalid parameter set.");

	if (upperBound > MAX_RANGE)
	{
		throw std::invalid_argument("Input parameter is more then 100'000'000.");
	}

	return upperBound;
}
