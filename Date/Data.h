#pragma once
#include <sstream>

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
	explicit CDate(unsigned timestamp = 0);
	CDate(unsigned day, Month month, unsigned year);

	unsigned GetDay() const;
	Month GetMonth() const;
	unsigned GetYear() const;
	WeekDay GetWeekDay() const;

	CDate& operator--();
	CDate& operator++();

	const CDate operator++(int);
	const CDate operator--(int);

	CDate operator+(unsigned days);

	CDate operator-(unsigned days);
	int operator-(CDate const& data);

	CDate& operator+=(unsigned days);
	CDate& operator-=(unsigned days);

	bool operator==(CDate const& other) const;
	bool operator!=(CDate const& other) const;

	bool operator>(CDate const& other) const;
	bool operator<(CDate const& other) const;

	bool operator<=(CDate const& other) const;
	bool operator>=(CDate const& other) const;

private:
	unsigned GetDaysBeforeData(unsigned day, Month const& month, unsigned year) const;

	unsigned GetCurrentEra() const;
	unsigned GetDayOfEra() const;
	unsigned GetYearOfEra() const;
	unsigned GetDayOfYear() const;

	unsigned GetShiftedMonthPositionFrom(Month const& normalMonth) const;
	unsigned GetDaysOfYearByMonthPosition(unsigned monthPosition) const;
	unsigned GetMonthPositionByDayOfYear(unsigned dayOfYear) const;

	bool IsDataValid(unsigned day, Month month, unsigned year) const;
	bool IsDataValid(unsigned daysAfter1970) const;

	unsigned m_daysAfter1970;
};

std::ostream& operator<<(std::ostream& out, CDate const& date);
std::istream& operator>>(std::istream& in, CDate& date);