#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "URLParser/URLParser.h"

namespace
{
	struct URLParams
	{
		Protocol protocol = Protocol::HTTP;
		std::string host = "";
		uint16_t port = 0;
		std::string document = "";
	};

	void RequireURLPort(std::string const& url, size_t portInt)
	{
		URLParams temp;
		REQUIRE(ParseURL(url, temp.protocol, temp.port, temp.host, temp.document));
		REQUIRE(temp.port == portInt);
	}

	void RequireFullURL(std::string const& url, URLParams const& urlParams)
	{
		URLParams temp;
		REQUIRE(ParseURL(url, temp.protocol, temp.port, temp.host, temp.document));
		REQUIRE(temp.protocol == urlParams.protocol);
		REQUIRE(temp.host == urlParams.host);
		REQUIRE(temp.port == urlParams.port);
		REQUIRE(temp.document == urlParams.document);
	}
}

TEST_CASE("Test Full URL")
{
	URLParams result;

	SECTION("Full url should be parsed successfully")
	{
		result.document = "docs/document1.html?page=30&lang=en#title";
		result.host = "www.mysite.com";
		result.port = 80;
		result.protocol = Protocol::HTTP;

		RequireFullURL("http://www.mysite.com/docs/document1.html?page=30&lang=en#title", result);
	}

	SECTION("Url without protocol should be return HTTP")
	{
		result.document = "doc";
		result.host = "example.ru";
		result.port = 1234;
		result.protocol = Protocol::HTTP;

		RequireFullURL("example.ru:1234/doc", result);
	}

	SECTION("Url without documents should be return empty")
	{
		result.document = "";
		result.host = "example.ru";
		result.port = 1234;
		result.protocol = Protocol::HTTPS;

		RequireFullURL("https://example.ru:1234", result);
	}
}

TEST_CASE("Test ports")
{
	SECTION("Default Http port should be 80")
	{
		RequireURLPort("http://example.ru", 80);
	}

	SECTION("Default Https port should be 443")
	{
		RequireURLPort("https://example.ru", 443);
	}

	SECTION("Default Ftp port should be 21")
	{
		RequireURLPort("ftp://example.ru", 21);
	}

	SECTION("Min port should be 1")
	{
		RequireURLPort("http://example.ru:1", 1);
	}

	SECTION("Max port should be 65535")
	{
		RequireURLPort("http://example.ru:65535", 65535);
	}
}

TEST_CASE("Test upper case")
{
	URLParams temp;
	REQUIRE(ParseURL("HTTP://example.ru", temp.protocol, temp.port, temp.host, temp.document));
	REQUIRE(temp.protocol == Protocol::HTTP);

	REQUIRE(ParseURL("HtTpS://example.ru", temp.protocol, temp.port, temp.host, temp.document));
	REQUIRE(temp.protocol == Protocol::HTTPS);
}

TEST_CASE("Test invalid")
{
	URLParams temp;

	SECTION("ParseURL with empty URL should be return false")
	{
		REQUIRE_FALSE(ParseURL("", temp.protocol, temp.port, temp.host, temp.document));
	}

	SECTION("ParseURL with invalid protocol should be return false")
	{
		REQUIRE_FALSE(ParseURL("hppt://example.ru", temp.protocol, temp.port, temp.host, temp.document));
	}

	SECTION("ParseURL with biggest protocol should be return false")
	{
		REQUIRE_FALSE(ParseURL("http://example.ru:65536", temp.protocol, temp.port, temp.host, temp.document));
	}

	SECTION("ParseURL with zero protocol should be return false")
	{
		REQUIRE_FALSE(ParseURL("http://example.ru:0000", temp.protocol, temp.port, temp.host, temp.document));
	}
}
