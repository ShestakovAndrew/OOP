#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Date/Data.h"

namespace
{
	void CheckExceptionInConstructorWithData(unsigned day, Month month, unsigned year)
	{
		try
		{
			CDate data(day, month, year);
		}
		catch (std::out_of_range const& error)
		{
			REQUIRE(error.what() == std::string("Object cannot be created with this value."));
		}
	}


}

TEST_CASE("CDate constructor should be create object correctly.")
{
	SECTION("Constructor by defult")
	{
		CDate data;

		REQUIRE(data.GetDay() == 1);
		REQUIRE(data.GetMonth() == Month::JANUARY);
		REQUIRE(data.GetWeekDay() == WeekDay::THURSDAY);
		REQUIRE(data.GetYear() == 1970);
	}
	
	SECTION("Constructor with year, month, day.")
	{
		SECTION("Data should be correctly.")
		{
			CDate data(1, Month::JANUARY, 1970);

			REQUIRE(data.GetWeekDay() == WeekDay::THURSDAY);
			REQUIRE(data.GetDay() == 1);
			REQUIRE(data.GetMonth() == Month::JANUARY);
			REQUIRE(data.GetYear() == 1970);

			CDate data2(31, Month::DECEMBER, 9999);

			REQUIRE(data2.GetWeekDay() == WeekDay::FRIDAY);
			REQUIRE(data2.GetDay() == 31);
			REQUIRE(data2.GetMonth() == Month::DECEMBER);
			REQUIRE(data2.GetYear() == 9999);
		}

		SECTION("Data lower.")
		{
			CheckExceptionInConstructorWithData(31, Month::DECEMBER, 1969);
		}

		SECTION("Data biggest.")
		{
			CheckExceptionInConstructorWithData(1, Month::JANUARY, 10000);
		}
	}
}
