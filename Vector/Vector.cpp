#include "Vector.h"

namespace
{
	const int8_t SIMBOLS_AFTER_COMMA = 3;
}

void SetRealNumbersTo(std::vector<double>& realNumbers)
{
	std::string lineFromUser;

	std::getline(std::cin, lineFromUser);
	std::istringstream iss(lineFromUser);

	std::string numberString;

	while (iss >> numberString)
	{
		realNumbers.push_back(boost::lexical_cast<double>(numberString));
	}
}

void GetSumAndCountPositiveNumbers(std::vector<double> const& realNumbers, double& numbersPositive—ount, double& numbersPositiveSum)
{
	std::for_each(realNumbers.begin(), realNumbers.end(),
		[&numbersPositive—ount, &numbersPositiveSum](double const& number)
		{
			if (number > 0)
			{
				numbersPositiveSum += number;
				numbersPositive—ount++;
			}
		}
	);
}

void AddNumberForAllElementsIn(std::vector<double>& realNumbers, double& numbersPositive—ount)
{
	std::for_each(realNumbers.begin(), realNumbers.end(),
		[&numbersPositive—ount](double& number)
		{
			number += numbersPositive—ount;
		}
	);
}

void AddAveragePositiveNumberForAllElementsIn(std::vector<double>& realNumbers)
{
	double numbersPositive—ount = 0;
	double numbersPositiveSum = 0;
	double numbersPositiveAverage = 0;

	GetSumAndCountPositiveNumbers(realNumbers, numbersPositive—ount, numbersPositiveSum);

	if (numbersPositive—ount != 0)
	{
		numbersPositiveAverage = numbersPositiveSum / numbersPositive—ount;
	}

	AddNumberForAllElementsIn(realNumbers, numbersPositiveAverage);
}

void PrintRealNumbers(std::vector<double>& realNumbers)
{
	for (auto& number : realNumbers)
	{
		std::cout << std::fixed << std::setprecision(SIMBOLS_AFTER_COMMA) << number << ' ';
	}
}
