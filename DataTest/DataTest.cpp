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

	void CheckExceptionInConstructorWithDaysAfter1970(unsigned daysAfter1970)
	{
		try
		{
			CDate data(daysAfter1970);
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

			CDate data3(19169);

			REQUIRE(data3.GetWeekDay() == WeekDay::SUNDAY);
			REQUIRE(data3.GetDay() == 26);
			REQUIRE(data3.GetMonth() == Month::JUNE);
			REQUIRE(data3.GetYear() == 2022);
		}

		SECTION("Data lower.")
		{
			CheckExceptionInConstructorWithData(31, Month::DECEMBER, 1969);
			CheckExceptionInConstructorWithDaysAfter1970(-1);
		}

		SECTION("Data biggest.")
		{
			CheckExceptionInConstructorWithData(1, Month::JANUARY, 10000);
			CheckExceptionInConstructorWithDaysAfter1970(MAX_DAYS_AFTER_1970 + 1);
		}
	}
}

TEST_CASE("Comparison operators should work correctly.")
{
	SECTION("Operator==")
	{
		CDate date1, date2;
		REQUIRE(date1 == date2);
		date1++;
		REQUIRE_FALSE(date1 == date2);
		date2++;
		REQUIRE(date1 == date2);
	}

	SECTION("Operator!=")
	{
		CDate date1, date2;
		REQUIRE_FALSE(date1 != date2);
		date1++;
		REQUIRE(date1 != date2);
		date2++;
		REQUIRE_FALSE(date1 != date2);
	}

	SECTION("Operator<")
	{
		CDate date1, date2;
		REQUIRE_FALSE(date1 < date2);
		date1++;
		REQUIRE(date2 < date1);
		date2++;
		REQUIRE_FALSE(date2 < date1);
	}

	SECTION("Operator>")
	{
		CDate date1, date2;
		REQUIRE_FALSE(date1 > date2);
		date1++;
		REQUIRE(date1 > date2);
		date2++;
		REQUIRE_FALSE(date1 > date2);
	}

	SECTION("Operator<=")
	{
		CDate date1, date2;
		REQUIRE(date1 <= date2);
		date1++;
		REQUIRE_FALSE(date1 <= date2);
		date2++;
		REQUIRE(date1 <= date2);
	}

	SECTION("Operator>=")
	{
		CDate date1, date2;
		REQUIRE(date1 >= date2);
		date1++;
		REQUIRE(date1 >= date2);
		date2 += 2;
		REQUIRE_FALSE(date1 >= date2);
	}
}

TEST_CASE("Date modification operators should work correctly.")
{
	SECTION("operator++")
	{
		CDate date1(10), data2(9);

		SECTION("prefix form")
		{
			REQUIRE(date1 == ++data2);
		}

		SECTION("postfix form")
		{
			++data2;
			REQUIRE(date1 == data2++);
		}

		SECTION("exceptions")
		{
			CDate date3(MAX_DAYS_AFTER_1970);
			REQUIRE_THROWS_AS(date3++, std::out_of_range);
			REQUIRE_THROWS_AS(++date3, std::out_of_range);
		}
	}

	SECTION("Operator--")
	{
		CDate date1(9), data2(10);

		SECTION("prefix form")
		{
			REQUIRE(date1 == --data2);
		}

		SECTION("postfix form")
		{
			--data2;
			REQUIRE(date1 == data2--);
		}

		SECTION("exceptions")
		{
			CDate date3;
			REQUIRE_THROWS_AS(date3--, std::out_of_range);
			REQUIRE_THROWS_AS(--date3, std::out_of_range);
		}
	}

	SECTION("Operator+")
	{
		CDate date1(28, Month::FEBRUARY, 2022);
		CDate date2(3, Month::MARCH, 2022);
		REQUIRE((date1 + 3) == date2);

		SECTION("exception")
		{
			CDate date3(MAX_DAYS_AFTER_1970);
			REQUIRE_THROWS_AS(date3 + 1, std::out_of_range);
		}
	}

	SECTION("Operator-")
	{
		SECTION("Subtract a given number of days from a date")
		{
			CDate date1(1, Month::JANUARY, 2022);
			CDate date2(30, Month::DECEMBER, 2021);
			REQUIRE((date1 - 2) == date2);

			SECTION("exception")
			{
				CDate date3;
				REQUIRE_THROWS_AS(date3 - 1, std::out_of_range);
			}
		}

		SECTION("Difference of two dates in days")
		{
			CDate date1(1, Month::JANUARY, 2022);
			CDate date2(30, Month::DECEMBER, 2021);
			REQUIRE((date1 - date2) == 2);

			CDate date3(1, Month::JANUARY, 2022);
			CDate date4(3, Month::JANUARY, 2022);
			REQUIRE((date3 - date4) == -2);
		}
	}

	SECTION("Operator+=")
	{
		CDate date1(15), date2(10);
		date2 += 5;
		REQUIRE(date1 == date2);

		SECTION("exception")
		{
			CDate date3(MAX_DAYS_AFTER_1970);
			REQUIRE_THROWS_AS(date3 += 1, std::out_of_range);
		}
	}

	SECTION("Operator-=")
	{
		CDate date1(15), date2(10);
		date1 -= 5;
		REQUIRE(date1 == date2);

		SECTION("exception")
		{
			CDate date3;
			REQUIRE_THROWS_AS(date3 -= 1, std::out_of_range);
		}
	}
}