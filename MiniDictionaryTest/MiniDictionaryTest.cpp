#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "MiniDictionary/MiniDictionary.h"

TEST_CASE("Should be returned translation of the words")
{
	Dictionary dictionary = {
		{ "cat", { "кот", "кошка" } },
		{ "ball", { "м€ч" } }
	};

	REQUIRE(GetWordTranslations(dictionary, "cat") == WordTranslations{ "кот", "кошка" });
	REQUIRE(GetWordTranslations(dictionary, "ball") == WordTranslations{ "м€ч" });
	REQUIRE(GetWordTranslations(dictionary, "meat") == WordTranslations{});
}

TEST_CASE("Should be returned translation of the phrases")
{
	Dictionary dictionary = {
		{ "great day", { "хороший день", "прекрасный день" } },
		{ "the red square", { " расна€ ѕлощадь" } }
	};

	REQUIRE(GetWordTranslations(dictionary, "great day") == WordTranslations{ "хороший день", "прекрасный день" });
	REQUIRE(GetWordTranslations(dictionary, "The Red Square") == WordTranslations{ " расна€ ѕлощадь" });
}

TEST_CASE("Should be returned translation of the phrases or words in any case")
{
	Dictionary dictionary = {
		{ "cat", { "кќт", "кќш ј" } },
		{ "ball", { "м€ч" } },
		{ "great day", { "хороший ƒ≈Ќ№", "прекрасный ƒ≈Ќ№" } },
		{ "the red square", { " расна€ ѕлощадь" } }
	};

	REQUIRE(GetWordTranslations(dictionary, "ThE ReD SqUaRe") == WordTranslations{ " расна€ ѕлощадь" });
	REQUIRE(GetWordTranslations(dictionary, "BALL") == WordTranslations{ "м€ч" });

	SECTION("Should be returned translation of the phrases or words in any case without losing the translation case")
	{
		REQUIRE(GetWordTranslations(dictionary, "GrEaT DaY") == WordTranslations{ "хороший ƒ≈Ќ№", "прекрасный ƒ≈Ќ№" });
		REQUIRE(GetWordTranslations(dictionary, "CaT") == WordTranslations{ "кќт", "кќш ј" });
	}
}

TEST_CASE("Should be returned reverse translation of the phrases or words")
{
	Dictionary dictionary = {
		{ "cat", { "кот", "кошка" } },
		{ "ball", { "м€ч" } },
		{ "great day", { "хороший день", "прекрасный день" } },
		{ "the red square", { " расна€ ѕлощадь" } }
	};

	REQUIRE(GetWordTranslations(dictionary, "хороший день") == WordTranslations{ "great day" });
	REQUIRE(GetWordTranslations(dictionary, "прекрасный день") == WordTranslations{ "great day" });
	REQUIRE(GetWordTranslations(dictionary, "кот") == WordTranslations{ "cat" });
	REQUIRE(GetWordTranslations(dictionary, "кошка") == WordTranslations{ "cat" });
	REQUIRE(GetWordTranslations(dictionary, "м€ч") == WordTranslations{ "ball" });

	SECTION("Should be returned reverse translation of the phrases or words in any case")
	{
		dictionary = {
		{ "cat", { "кот", "кошка" } },
		{ "ball", { "м€ч" } },
		{ "great day", { "хороший день", "прекрасный день" } },
		{ "the red square", { " расна€ ѕлощадь" } }
		};

		REQUIRE(GetWordTranslations(dictionary, "’о–оЎи… ƒеЌь") == WordTranslations{ "great day" });
		REQUIRE(GetWordTranslations(dictionary, "п–е рјсЌы… ƒеЌь") == WordTranslations{ "great day" });
		REQUIRE(GetWordTranslations(dictionary, " ќ“") == WordTranslations{ "cat" });
		REQUIRE(GetWordTranslations(dictionary, " ќЎ ј") == WordTranslations{ "cat" });
		REQUIRE(GetWordTranslations(dictionary, "мяч") == WordTranslations{ "ball" });
	}
}

TEST_CASE("should be correctly add new words and phrases to the dictionary")
{
	Dictionary dictionary = {
		{ "cat", { "кот" } },
		{ "ball", { "м€ч" } },
		{ "the red square", { " расна€ ѕлощадь" } }
	};

	AddTranslationInDictionary("кошка", "cat", dictionary);
	AddTranslationInDictionary("evil cat", "кошјрј", dictionary);
	AddTranslationInDictionary("meet", "м€со", dictionary);

	Dictionary requiredDictionary = {
		{ "cat", { "кот", "кошка" }},
		{ "evil cat", { "кошјрј" }},
		{ "ball", { "м€ч" } },
		{ "meet", { "м€со" } },
		{ "the red square", { " расна€ ѕлощадь" } },
	};

	REQUIRE(dictionary == requiredDictionary);
}

