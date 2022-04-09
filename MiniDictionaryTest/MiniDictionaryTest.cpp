#define BOOST_TEST_MAIN
#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include "MiniDictionary/MiniDictionary.h"

#include <boost/test/tools/output_test_stream.hpp>
#include <boost/test/unit_test.hpp>

namespace
{
	struct cout_redirect
	{
		cout_redirect(std::streambuf* new_buffer)
			: old(std::cout.rdbuf(new_buffer))
		{ }

		~cout_redirect()
		{
			std::cout.rdbuf(old);
		}

	private:
		std::streambuf* old;
	};
}

TEST_CASE("FindWordInDictionary function")
{
	SECTION("Find word in dictionary and get translation.")
	{
		boost::test_tools::output_test_stream output;
		{
			cout_redirect guard(output.rdbuf());
			std::multimap<std::string, std::string> dictionary;
			dictionary.insert(std::pair<std::string, std::string >("walk", "ходить"));
			const std::string userString = "walk";
			std::string userTranslation = "ходить";
			bool isDictionaryChanged = false;
			FindWordInDictionary(dictionary, userString, userTranslation, isDictionaryChanged);
		}

		REQUIRE(output.is_equal("ходить \n"));
	}

	SECTION("Without word in dictionary.")
	{
		boost::test_tools::output_test_stream output;
		{
			cout_redirect guard(output.rdbuf());
			std::multimap<std::string, std::string> dictionary;
			dictionary.insert(std::pair<std::string, std::string>("celebrate", "праздновать"));
			const std::string userString = "rage";
			std::string userTranslation = "злиться";
			bool isDictionaryChanged = false;
			FindWordInDictionary(dictionary, userString, userTranslation, isDictionaryChanged);
		}
		REQUIRE(output.is_equal("Неизвестное слово 'rage'. Введите перевод или пустую строку для отказа.\nСлово 'rage' проигнорировано.\n"));
	}

	SECTION("Translate phrases.")
	{
		boost::test_tools::output_test_stream output;
		{
			cout_redirect guard(output.rdbuf());
			std::multimap<std::string, std::string> dictionary;
			dictionary.insert(std::pair<std::string, std::string>("good day", "хороший день"));
			const std::string userString = "good day";
			std::string userTranslation = "хороший день";
			bool isDictionaryChanged = false;
			FindWordInDictionary(dictionary, userString, userTranslation, isDictionaryChanged);
		}
		REQUIRE(output.is_equal("хороший день \n"));
	}

	SECTION("Multy-translations.")
	{
		boost::test_tools::output_test_stream output;
		{
			cout_redirect guard(output.rdbuf());
			std::multimap<std::string, std::string> dictionary;
			dictionary.insert(std::pair<std::string, std::string>("cat", "кошка"));
			dictionary.insert(std::pair<std::string, std::string>("cat", "кот"));
			const std::string userString = "cat";
			std::string userTranslation = "кошка";
			bool isDictionaryChanged = false;
			FindWordInDictionary(dictionary, userString, userTranslation, isDictionaryChanged);
		}
		REQUIRE(output.is_equal("кошка кот \n"));
	}
}

