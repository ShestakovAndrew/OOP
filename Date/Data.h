#pragma once
#include <sstream>

const unsigned YEARS_IN_CENTURY = 100;
const unsigned YEARS_IN_ERA = 400;
const unsigned DAYS_IN_ERA = 146097;
const unsigned DAYS_IN_BASE_YEAR = 365;
const unsigned DAYS_BETWEEN_FIRST_ERA_AND_1970 = 719468; // from 0000-03-01 to 1970-01-01;
const unsigned DAYS_IN_100_YEARS_OF_EAR = 36524;
const unsigned DAYS_IN_4_YEARS_OF_EAR = 1460;
const unsigned MAX_DAYS_AFTER_1970 = 2932896;

enum class Month
{
	JANUARY = 1, FEBRUARY, MARCH, APRIL,
	MAY, JUNE, JULY, AUGUST, SEPTEMBER,
	OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
	SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
	THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
public:
	explicit CDate(unsigned daysAfter1970 = 0);
	CDate(unsigned day, Month month, unsigned year);

	unsigned GetDay() const noexcept;
	Month GetMonth() const noexcept;
	unsigned GetYear() const noexcept;
	WeekDay GetWeekDay() const noexcept;

	CDate& operator--();
	CDate& operator++();

	const CDate operator++(int);
	const CDate operator--(int);

	CDate& operator+=(unsigned days);
	CDate& operator-=(unsigned days);

	CDate operator+(unsigned days);
	CDate operator-(unsigned days);

	int operator-(CDate const& data) const noexcept;

	bool operator==(CDate const& other) const noexcept;
	bool operator!=(CDate const& other) const noexcept;

	bool operator>(CDate const& other) const noexcept;
	bool operator<(CDate const& other) const noexcept;

	bool operator<=(CDate const& other) const noexcept;
	bool operator>=(CDate const& other) const noexcept;

	friend std::istream& operator>>(std::istream& in, CDate& date);
	friend std::ostream& operator<<(std::ostream& out, CDate date);

private:
	unsigned CountDaysAfter1970(unsigned day, Month const& month, unsigned year) const noexcept;

	unsigned GetCurrentEra() const noexcept;
	unsigned GetDayOfEra() const noexcept;
	unsigned GetYearOfEra() const noexcept;
	unsigned GetDayOfYear() const noexcept;

	unsigned GetShiftedMonthPositionFrom(Month const& normalMonth) const noexcept;
	unsigned GetDaysOfYearByMonthPosition(unsigned monthPosition) const noexcept;
	unsigned GetMonthPositionByDayOfYear(unsigned dayOfYear) const noexcept;

	bool IsDataValid(unsigned day, Month month, unsigned year) const noexcept;
	bool IsDataValid(unsigned daysAfter1970) const noexcept;

	unsigned m_daysAfter1970;
};