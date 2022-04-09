#include "HTMLDecode.h"

void DecodeHtmlDocument(std::istream& input, std::ostream& output)
{
	std::string htmlLine;
	while (getline(input, htmlLine))
	{
		output << HtmlDecode(htmlLine) << std::endl;
	}
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	try
	{
		DecodeHtmlDocument(std::cin, std::cout);
	}
	catch (const std::bad_cast& error)
	{
		std::cout << error.what() << std::endl;
		return 1;
	}
}