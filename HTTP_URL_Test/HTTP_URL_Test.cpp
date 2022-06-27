#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "HTTP_URL/HttpUrl.h"

TEST_CASE("Constructor that takes URL must parse it")
{
	CHttpUrl url("https://www.site:123/docs/document.html");
	REQUIRE(url.GetDomain() == "www.site");
	REQUIRE(url.GetDocument() == "/docs/document.html");
	REQUIRE(url.GetProtocol() == Protocol::HTTPS);
	REQUIRE(url.GetPort() == 123);

	CHttpUrl url1("http://www.site");
	REQUIRE(url1.GetDomain() == "www.site");
	REQUIRE(url1.GetDocument() == "/");
	REQUIRE(url1.GetProtocol() == Protocol::HTTP);
	REQUIRE(url1.GetPort() == 80);

	SECTION("If failed, an exception must be thrown")
	{
		REQUIRE_THROWS_AS(CHttpUrl("http:///my.com"), std::exception);
		REQUIRE_THROWS_AS(CHttpUrl("httpq://my.com"), std::exception);
		REQUIRE_THROWS_AS(CHttpUrl("http://my.com:65536"), std::exception);
	}
}

TEST_CASE("Constructor, that takes domain, document, [protocol], must initialize url")
{
	CHttpUrl url("www.site", "/doc", Protocol::HTTPS);
	REQUIRE(url.GetDomain() == "www.site");
	REQUIRE(url.GetDocument() == "/doc");
	REQUIRE(url.GetProtocol() == Protocol::HTTPS);
	REQUIRE(url.GetPort() == 443);

	SECTION("Default protocol must be HTTP")
	{
		CHttpUrl url1("www.site", "/doc");
		REQUIRE(url1.GetProtocol() == Protocol::HTTP);
	}

	SECTION("If document doesn't start with '/', then constructor must add '/'")
	{
		CHttpUrl url1("www.site", "doc");
		REQUIRE(url1.GetDocument() == "/doc");

		CHttpUrl url2("www.site", "");
		REQUIRE(url2.GetDocument() == "/");
	}

	SECTION("If failed, an exception must be thrown")
	{
		REQUIRE_THROWS_AS(CHttpUrl("", "/doc"), std::exception);
	}
}

TEST_CASE("Constructor, that takes domain, document, protocol, port, must initialize url")
{
	CHttpUrl url("www.site", "/doc", Protocol::HTTPS, 123);
	REQUIRE(url.GetDomain() == "www.site");
	REQUIRE(url.GetDocument() == "/doc");
	REQUIRE(url.GetProtocol() == Protocol::HTTPS);
	REQUIRE(url.GetPort() == 123);

	SECTION("If document doesn't start with '/', then constructor must add '/'")
	{
		CHttpUrl url1("www.site", "doc", Protocol::HTTPS, 123);
		REQUIRE(url1.GetDocument() == "/doc");

		CHttpUrl url2("www.site", "", Protocol::HTTPS, 123);
		REQUIRE(url2.GetDocument() == "/");
	}

	SECTION("If failed, an exception must be thrown")
	{
		REQUIRE_THROWS_AS(CHttpUrl("", "/doc", Protocol::HTTPS, 123), std::exception);
		REQUIRE_THROWS_AS(CHttpUrl("www.site", "/doc", Protocol::HTTP, 0), std::exception);
	}
}

TEST_CASE("GetUrl() must return url string representation")
{
	CHttpUrl url1("www.site", "doc", Protocol::HTTPS, 123);
	REQUIRE(url1.GetURL() == "https://www.site:123/doc");

	SECTION("Standard port for HTTP and HTTPS mustn't be included in string")
	{
		CHttpUrl url2("www.site", "doc", Protocol::HTTP);
		REQUIRE(url2.GetURL() == "http://www.site/doc");
	}
}

TEST_CASE("If port is not specified, then it must be default for HTTP and HTTPS")
{
	CHttpUrl url1("www.site", "doc", Protocol::HTTP);
	CHttpUrl url2("www.site", "doc", Protocol::HTTPS);

	REQUIRE(url1.GetPort() == 80);
	REQUIRE(url2.GetPort() == 443);
}

TEST_CASE("Protocol can be in any register")
{
	CHttpUrl url("Http://127.0.0.1/12");

	REQUIRE(url.GetDomain() == "127.0.0.1");
	REQUIRE(url.GetDocument() == "/12");
	REQUIRE(url.GetProtocol() == Protocol::HTTP);
	REQUIRE(url.GetPort() == 80);
}