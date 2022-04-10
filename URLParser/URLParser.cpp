#include "URLParser.h"

const std::string PROTOCOL_REGEX = R"((?:(https?|ftp):\/\/)?)";
const std::string HOST_REGEX = R"(([^:\s\/\\?#]+))";
const std::string PORT_REGEX = R"((?::(\d+))?)";
const std::string DOC_REGEX = R"((?:\/((?:[^:\/\\]+\/?)*))?)";

const uint16_t DEFAULT_HTTP_PORT = 80;
const uint16_t DEFAULT_HTTPS_PORT = 443;
const uint16_t DEFAULT_FTP_PORT = 21;

const uint16_t MIN_PORT = 1;
const uint16_t MAX_PORT = 65535;

bool ParseURL(std::string const& url, Protocol& protocol, uint16_t& port, std::string& host, std::string& document)
{
	std::string regexStr;

	try
	{
		regexStr = (boost::format("^%s%s%s%s$") % PROTOCOL_REGEX % HOST_REGEX % PORT_REGEX % DOC_REGEX).str();
	}
	catch (boost::io::format_error&)
	{
		return false;
	}

	std::regex reg(regexStr, std::regex_constants::icase);
	std::smatch match;

	if (!std::regex_match(url, match, reg)) return false;

	try
	{
		protocol = ProtocolFromString(std::string(match[1].first, match[1].second));
		host = std::string(match[2].first, match[2].second);
		port = PortFromString(std::string(match[3].first, match[3].second), protocol);
		document = std::string(match[4].first, match[4].second);
	}
	catch (std::exception const&)
	{
		return false;
	}

	return true;
}

uint16_t GetDefaultProtocol(Protocol const& protocol)
{
	switch (protocol)
	{
	case Protocol::HTTP:
		return DEFAULT_HTTP_PORT;
	case Protocol::HTTPS:
		return DEFAULT_HTTPS_PORT;
	case Protocol::FTP:
		return DEFAULT_FTP_PORT;
	}

	throw std::invalid_argument("Protocol not found.");
}

Protocol ProtocolFromString(std::string const& str)
{
	std::string lowerStr(boost::algorithm::to_lower_copy<std::string>(str));

	if (lowerStr == "http" || lowerStr.empty())
	{
		return Protocol::HTTP;
	}
	else if (lowerStr == "https")
	{
		return Protocol::HTTPS;
	}
	else if (lowerStr == "ftp")
	{
		return Protocol::FTP;
	}
	else throw std::invalid_argument("Wrong protocol: " + lowerStr);
}

uint16_t PortFromString(std::string const& str, Protocol const& protocol)
{
	if (str.empty()) return GetDefaultProtocol(protocol);

	uint16_t port = 0;

	try
	{
		port = boost::lexical_cast<uint16_t>(str);
	}
	catch (std::bad_cast const&)
	{
		throw std::invalid_argument("Wrong port: " + str);
	}

	if (port < MIN_PORT || port > MAX_PORT)
	{
		throw std::out_of_range("Port should be in range " + std::to_string(MIN_PORT) + " - " + std::to_string(MAX_PORT));
	}

	return port;
}
