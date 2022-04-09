#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "HTMLDecode/HTMLDecode.h"

TEST_CASE("Successful replacement")
{
	SECTION("Empty string should be empty")
	{
		REQUIRE("" == HtmlDecode(""));
	}

	SECTION("&quot; should be decode to double quotation mark")
	{
		REQUIRE("\"" == HtmlDecode("&quot;"));
	}

	SECTION("&apos; should be decode to apostrophe")
	{
		REQUIRE("'" == HtmlDecode("&apos;"));
	}

	SECTION("&lt; should be decode to less than")
	{
		REQUIRE("<" == HtmlDecode("&lt;"));
	}

	SECTION("&gt; should be decode to greater than")
	{
		REQUIRE(">" == HtmlDecode("&gt;"));
	}

	SECTION("&amp; should be decode to ampersand")
	{
		REQUIRE("&" == HtmlDecode("&amp;"));
	}

	SECTION("All html entities")
	{
		REQUIRE("\"'<>&" == HtmlDecode("&quot;&apos;&lt;&gt;&amp;"));
	}

	SECTION("Double ampersand before html entities.")
	{
		REQUIRE("&\"&'&<&>&&" == HtmlDecode("&&quot;&&apos;&&lt;&&gt;&&amp;"));
	}

	SECTION("Meow sentence")
	{
		REQUIRE("Cat <says> \"Meow\". M&M's" == HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s"));
	}

	SECTION("Replacing in a chaotic manner.")
	{
		REQUIRE(">>\"&<\"'&<\">&\"<>" == HtmlDecode("&gt;&gt;&quot;&amp;&lt;&quot;&apos;&amp;&lt;&quot;&gt;&amp;&quot;&lt;&gt;"));
	}
}