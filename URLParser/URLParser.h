#pragma once
#include <iostream>
#include <string>
#include <regex>

#include "boost/lexical_cast.hpp"
#include "boost/format.hpp"
#include "boost/algorithm/string.hpp"

enum class Protocol
{
	HTTP = 0,
	HTTPS,
	FTP
};

bool ParseURL(std::string const& url, Protocol& protocol, uint16_t& port, std::string& host, std::string& document);

uint16_t GetDefaultProtocol(Protocol const& protocol);

Protocol ProtocolFromString(std::string const& str);

uint16_t PortFromString(std::string const& str, Protocol const& protocol);