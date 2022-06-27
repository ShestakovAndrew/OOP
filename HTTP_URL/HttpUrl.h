#pragma once
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol const& protocol = Protocol::HTTP);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol const& protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const noexcept;
	std::string GetDocument() const noexcept;
	Protocol GetProtocol() const noexcept;
	unsigned short GetPort() const noexcept;

	static std::string ProtocolToString(Protocol const& protocol);

private:
	void ParseUrl(std::string const& url);

	Protocol StringToProtocol(std::string protocol);

	unsigned short GetDefaultPort(Protocol const& protocol) const;
	unsigned short GetPort(std::string const& port, Protocol const& protocol) const;
	std::string GetUrlDocument(std::string const& document) const noexcept;

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};