#include "GeneratorSimplesNumbers.h"

namespace
{
	static const int64_t MAX_RANGE = 100'000'000;
}

std::vector<bool> SelectPrimeNumbers(size_t upperBound)
{
	std::vector<bool> isPrime(upperBound + 1, true);

	for (size_t i = 2; i * i <= upperBound; i++)
	{
		if (isPrime[i])
		{
			for (size_t j = i * i; j <= upperBound; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	return isPrime;
}

std::set<size_t> GenerateSet(std::vector<bool> const& numbers)
{
	std::set<size_t> selectedNumbers;

	for (size_t i = 2; i < numbers.size(); i++)
	{
		if (numbers[i]) selectedNumbers.insert(i);
	}

	return selectedNumbers;
}

std::set<size_t> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<size_t> setOfPrime = {};

	if (upperBound < 2) return setOfPrime;

	std::vector<bool> selectedPrimes = SelectPrimeNumbers(upperBound);

	return GenerateSet(selectedPrimes);
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

void DisplayPrimeNumbers(std::set<size_t> const& primeNumbers)
{
	for (auto it = primeNumbers.cbegin(); it != primeNumbers.cend(); ++it)
	{
		std::cout << *it + 1 << ' ';
	}
}

int GetUpperBound(int argc, const char* argv[])
{
	CheckArguments(argc, argv);

	int upperBound = std::atoi(argv[1]);

	if (!upperBound) throw std::invalid_argument("Invalid parameter set.");

	if (upperBound > MAX_RANGE)
	{
		throw std::invalid_argument("Input parameter is more then 100'000'000.");
	}

	return upperBound;
}
