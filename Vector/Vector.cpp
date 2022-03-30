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
	using RealNumbers = std::vector<double>;
}

void SetRealNumbersFromUserTo(RealNumbers& realNumbers)
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

void AddMeanPositiveNumberForAllElementsIn(RealNumbers& realNumbers)
{
	std::for_each(realNumbers.begin(), realNumbers.end(), [realNumbers](double& number)
	{
		double sum = 0;
		std::for_each(realNumbers.begin(), realNumbers.end(),
			[&sum](double number) { if (number > 0) sum += number; });

		number += sum / double(std::count_if(realNumbers.begin(), realNumbers.end(), [](double number)
			{return number > 0; }));
	});
}

void PrintRealNumbers(RealNumbers const& realNumbers)
{
	for (auto const& number : realNumbers)
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
		RealNumbers sequence;

		SetRealNumbersFromUserTo(sequence);
		AddMeanPositiveNumberForAllElementsIn(sequence);
		PrintRealNumbers(sequence);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}


}
