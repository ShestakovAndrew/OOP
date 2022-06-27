#include <map>
#include <regex>
#include <stdexcept>

#include "HttpUrl.h"
#include "UrlParsingError.h"

namespace
{
	static const std::map<Protocol, unsigned short> DEFAULT_PORT = {
		{ Protocol::HTTP, 80 },
		{ Protocol::HTTPS, 443 }
	};
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	try
	{
		ParseUrl(url);
	}
	catch (std::invalid_argument const& error)
	{
		throw CUrlParsingError(error.what());
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol const& protocol)
	: CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol const& protocol, unsigned short port)
{
	if (domain.empty()) throw std::invalid_argument("Domain mustn't be empty");
	if (port < 1 || port > 65535) throw std::invalid_argument("Invalid port. Port must be in segment [1, 65535]");

	m_domain = domain;
	m_document = GetUrlDocument(document);
	m_protocol = protocol;
	m_port = port;
}

std::string CHttpUrl::GetURL() const
{
	std::string port = (m_port != GetDefaultPort(m_protocol))
		? ":" + std::to_string(m_port)
		: "";

	return ProtocolToString(m_protocol) + "://" + m_domain + port + m_document;
}
std::string CHttpUrl::GetDomain() const noexcept
{
	return m_domain;
}
std::string CHttpUrl::GetDocument() const noexcept
{
	return m_document;
}
Protocol CHttpUrl::GetProtocol() const noexcept
{
	return m_protocol;
}
unsigned short CHttpUrl::GetPort() const noexcept
{
	return m_port;
}

std::string CHttpUrl::ProtocolToString(Protocol const& protocol)
{
	if (protocol == Protocol::HTTP) return "http";
	else if (protocol == Protocol::HTTPS) return "https";
	else throw std::runtime_error("Protocol string representation doesn't exist.");
}
Protocol CHttpUrl::StringToProtocol(std::string protocol)
{
	std::transform(protocol.begin(), protocol.end(), protocol.begin(), tolower);

	if (protocol == "http") return Protocol::HTTP;
	else if (protocol == "https") return Protocol::HTTPS;
	else throw std::invalid_argument("Invalid protocol.");
}

void CHttpUrl::ParseUrl(std::string const& url)
{
	std::smatch matches;
	std::regex regex("^([[:alpha:]]+)://([-.[:alnum:]]+)(:([[:digit:]]+))?(/(.*))?$");
	std::regex_search(url, matches, regex);

	if (matches.empty())
	{
		throw std::invalid_argument("Invalid url. Format: <protocol>://<domain>[:<port>][/<document>]");
	}

	m_protocol = StringToProtocol(matches[1]);
	m_domain = matches[2];
	m_port = GetPort(matches[4], m_protocol);
	m_document = GetUrlDocument(matches[6]);
}

unsigned short CHttpUrl::GetDefaultPort(Protocol const& protocol) const
{
	auto it = DEFAULT_PORT.find(protocol);

	if (it != DEFAULT_PORT.end()) return it->second;
	else throw std::runtime_error("Protocol doesn't have default port.");
}

std::string CHttpUrl::GetUrlDocument(std::string const& document) const noexcept
{
	return (document.empty() || document[0] != '/') 
		? ('/' + document) 
		: document;
}

unsigned short CHttpUrl::GetPort(std::string const& port, Protocol const& protocol) const
{
	if (port.empty()) return GetDefaultPort(protocol);

	int resultPort = atoi(port.c_str());

	if (resultPort >= 1 && resultPort <= 65535) return resultPort;
	else throw std::invalid_argument("Invalid port. Port should be in [1, 65535]");
}
