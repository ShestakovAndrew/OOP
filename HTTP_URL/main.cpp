#include "HttpUrl.h"
#include "UrlParsingError.h"
#include <iostream>
#include <string>

int main()
{
	std::string input;
	while (getline(std::cin, input))
	{
		try
		{
			CHttpUrl url(input);
			std::cout << "Protocol: " << CHttpUrl::ProtocolToString(url.GetProtocol()) << std::endl
				<< "Domain: " << url.GetDomain() << std::endl
				<< "Port: " << std::to_string(url.GetPort()) << std::endl
				<< "Document: " << url.GetDocument() << std::endl
				<< "Url: " << url.GetURL() << std::endl;
		}
		catch (CUrlParsingError const& error)
		{
			std::cout << error.what() << std::endl;
		}
		catch (std::runtime_error const& error)
		{
			std::cout << error.what() << std::endl;
		}
	}

	return 0;
}