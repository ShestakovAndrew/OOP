#include "URLParser.h"

int main()
{
	std::string url;
	while (std::getline(std::cin, url))
	{
		Protocol protocol;
		std::string host;
		uint16_t port = 0;
		std::string document;

		if (!ParseURL(url, protocol, port, host, document))
		{
			std::cout << "Invalid url." << std::endl;
		}
		else
		{
			std::cout << "HOST: " << host << std::endl;
			std::cout << "PORT: " << port << std::endl;
			std::cout << "DOC: " << document << std::endl;
		}
		std::cout << std::endl;
	}
}