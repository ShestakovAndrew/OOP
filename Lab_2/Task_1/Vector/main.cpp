#include "Vector.h"

int main(int argc, char* argv[])
{
	try
	{
		std::vector<double> sequence;
		SetRealNumbersTo(sequence);
		AddAveragePositiveNumberForAllElementsIn(sequence);
		std::sort(sequence.begin(), sequence.end());
		PrintRealNumbers(sequence);
	}
	catch (const std::exception& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}