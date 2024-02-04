#include <iostream>
#include <string>
#include <unordered_map>

#include <boost/program_options.hpp>

namespace
{
	enum class Answer
	{
		MAGIC,
		NON_MAGIC,
		ERROR
	};

	std::unordered_map<Answer, std::string> const answerTable = {
			{Answer::MAGIC, "Magic"},
			{Answer::NON_MAGIC, "Non-magic"},
			{Answer::ERROR, "Error"},
	};
}

uint8_t GetSumDigits(uint64_t number)
{
	uint8_t result = 0; 

	while (number > 0)
	{
		result += number % 10;
		number /= 10;
	}

	return result;
}

bool IsMagicNumber(uint64_t number)
{
	return (number - GetSumDigits(number)) % 9 != 0;
}

void InteractiveMode()
{
	std::string numberStr;

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		std::getline(std::cin, numberStr);

		try
		{
			uint64_t number = static_cast<uint64_t>(std::stoull(numberStr));

			std::cout << "> " + answerTable.at(
				IsMagicNumber(number) ? Answer::MAGIC : Answer::NON_MAGIC) << std::endl;
		}
		catch (const std::exception&)
		{
			std::cout << "> " + answerTable.at(Answer::ERROR) << std::endl;
		}
	}
}

void SearchMode(uint64_t N)
{
	for (size_t number = 1; number <= N; number++)
	{
		std::cout << "> " << number << ": " << answerTable.at(
			IsMagicNumber(number) ? Answer::MAGIC : Answer::NON_MAGIC) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");

	boost::program_options::options_description desc("Allowed options");
	boost::program_options::variables_map args;

	try
	{
		desc.add_options()
			("find", boost::program_options::value<uint64_t>(), "arg: [0;2^64-1]")
		;
		
		boost::program_options::store(
			boost::program_options::parse_command_line(argc, argv, desc), 
			args
		);

		boost::program_options::notify(args);
		args.count("find") ? SearchMode(args["find"].as<uint64_t>()) : InteractiveMode();
	}
	catch (boost::program_options::error const&)
	{
		std::cout << desc << std::endl;
		return 1;
	}

	return 0;
}