#include <iostream>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>

#include <boost/lexical_cast.hpp>

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

void AddMeanPositiveNumberForAllElementsIn(std::vector<double>& realNumbers)
{
	double numbersPositive—ount = 0, numbersPositiveSum = 0;

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

	double arithmeticMeanOfPositiveNumbers = numbersPositiveSum / numbersPositive—ount;


	std::for_each(realNumbers.begin(), realNumbers.end(),
		[&arithmeticMeanOfPositiveNumbers](double& number)
		{
			number += arithmeticMeanOfPositiveNumbers;
		}
	);
}

void PrintRealNumbers(std::vector<double>& realNumbers)
{
	std::sort(realNumbers.begin(), realNumbers.end());
	for (auto& number : realNumbers)
	{
		std::cout << std::fixed << std::setprecision(SIMBOLS_AFTER_COMMA) << number << ' ';
	}
}

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
