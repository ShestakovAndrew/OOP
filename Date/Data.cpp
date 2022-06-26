#include "Data.h"
#include <iomanip>
#include <unordered_map>

namespace
{
	void operator++(Month& month)
	{
		month = static_cast<Month>((static_cast<int>(month) + 1) % 12);
	}

	unsigned ToInt(Month const& month)
	{
		return static_cast<unsigned>(month);
	}

	Month ToMonth(unsigned numberOfMonth)
	{
		return static_cast<Month>(numberOfMonth);
	}

}

CDate::CDate(unsigned day, Month month, unsigned year)
{
	if (IsDataValid(day, month, year))
	{
		m_daysAfter1970 = GetDaysBeforeData(day, month, year);
	}
	else
	{
		throw std::out_of_range("Object cannot be created with this value.");
	}
}

CDate::CDate(unsigned daysAfter1970)
{
	if (IsDataValid(daysAfter1970))
	{
		m_daysAfter1970 = daysAfter1970;
	}
	else
	{
		throw std::out_of_range("Object cannot be created with this value.");
	}
}

unsigned CDate::GetDaysBeforeData(unsigned day, Month const& month, unsigned year) const
{
	if (month <= Month::FEBRUARY) year--;

	unsigned currentEra = year / YEARS_IN_ERA; // first era is 0000 - 0400 years and etc;
	unsigned yearOfEra = year % YEARS_IN_ERA; // 2022 % 400 = 22 year;

	unsigned newMonth = GetShiftedMonthPositionFrom(month);
	unsigned dayOfYear = GetDaysOfYearByMonthPosition(newMonth) + day - 1;

	unsigned dayOfEra = yearOfEra * DAYS_IN_BASE_YEAR
		+ yearOfEra / 4
		- yearOfEra / 100
		+ dayOfYear;

	return currentEra * DAYS_IN_ERA + dayOfEra - DAYS_BETWEEN_FIRST_ERA_AND_1970;
}

unsigned CDate::GetCurrentEra() const
{
	return (m_daysAfter1970 + DAYS_BETWEEN_FIRST_ERA_AND_1970) / DAYS_IN_ERA;
}
unsigned CDate::GetDayOfEra() const
{
	return (m_daysAfter1970 + DAYS_BETWEEN_FIRST_ERA_AND_1970) % DAYS_IN_ERA;
}
unsigned CDate::GetYearOfEra() const
{
	unsigned dayOfEra = GetDayOfEra();
	return (dayOfEra 
		- dayOfEra / DAYS_IN_4_YEARS_OF_EAR
		+ dayOfEra / DAYS_IN_100_YEARS_OF_EAR
		- dayOfEra / (DAYS_IN_ERA - 1)) / DAYS_IN_BASE_YEAR;
}
unsigned CDate::GetDayOfYear() const
{
	unsigned dayOfEra = GetDayOfEra();
	unsigned yearOfEra = GetYearOfEra();
	return dayOfEra - (
		DAYS_IN_BASE_YEAR * yearOfEra
		+ yearOfEra / 4
		- yearOfEra / YEARS_IN_CENTURY
	);
}

WeekDay CDate::GetWeekDay() const
{
	switch (m_daysAfter1970 % 7)
	{
		case 0: return WeekDay::THURSDAY;
		case 1: return WeekDay::FRIDAY;
		case 2: return WeekDay::SATURDAY;
		case 3: return WeekDay::SUNDAY;
		case 4: return WeekDay::MONDAY;
		case 5: return WeekDay::TUESDAY;
		default: return WeekDay::WEDNESDAY;
	}
}
unsigned CDate::GetDay() const
{
	unsigned dayOfYear = GetDayOfYear();
	unsigned shiftedMonthPosition = GetMonthPositionByDayOfYear(dayOfYear);
	return dayOfYear - GetDaysOfYearByMonthPosition(shiftedMonthPosition) + 1;
}
Month CDate::GetMonth() const
{
	unsigned shiftedMonthPosition = GetMonthPositionByDayOfYear(GetDayOfYear());
	return ToMonth((shiftedMonthPosition < 10) 
		? shiftedMonthPosition + 3 
		: shiftedMonthPosition - 9
	);
}
unsigned CDate::GetYear() const
{
	unsigned year = GetYearOfEra() + (GetCurrentEra() * YEARS_IN_ERA);
	return (GetMonth() <= Month::FEBRUARY) ? year += 1 : year;
}

CDate& CDate::operator++()
{
	if (!IsDataValid(m_daysAfter1970 + 1))
	{
		throw std::out_of_range("Your data out of range. Correct range is 1/1/1970 - 31.12.9999.");
	}

	++m_daysAfter1970;
	return *this;
}
CDate const CDate::operator++(int)
{
	if (!IsDataValid(m_daysAfter1970 + 1))
	{
		throw std::out_of_range("Your data out of range. Correct range is 1/1/1970 - 31.12.9999.");
	}

	CDate temp(m_daysAfter1970);
	m_daysAfter1970++;
	return temp;
}
CDate& CDate::operator--()
{
	if (!IsDataValid(m_daysAfter1970 - 1))
	{
		throw std::out_of_range("Your data out of range. Correct range is 1/1/1970 - 31.12.9999.");
	}

	--m_daysAfter1970;
	return *this;
}
CDate const CDate::operator--(int)
{
	if (!IsDataValid(m_daysAfter1970 - 1))
	{
		throw std::out_of_range("Your data out of range. Correct range is 1/1/1970 - 31.12.9999.");
	}

	CDate temp(m_daysAfter1970);
	m_daysAfter1970--;
	return temp;
}
CDate CDate::operator+(unsigned days) const
{
	if (!IsDataValid(m_daysAfter1970 + days))
	{
		throw std::out_of_range("Your data out of range. Correct range is 1/1/1970 - 31.12.9999.");
	}

	return CDate(m_daysAfter1970 + days);
}
CDate CDate::operator-(unsigned days) const
{
	if (!IsDataValid(m_daysAfter1970 - days))
	{
		throw std::out_of_range("Your data out of range. Correct range is 1/1/1970 - 31.12.9999.");
	}

	return CDate(m_daysAfter1970 - days);
}
int CDate::operator-(CDate const& data) const noexcept
{
	return m_daysAfter1970 - data.m_daysAfter1970;
}
CDate& CDate::operator+=(unsigned days)
{
	if (!IsDataValid(m_daysAfter1970 + days))
	{
		throw std::out_of_range("Your data out of range. Correct range is 1/1/1970 - 31.12.9999.");
	}

	m_daysAfter1970 += days;
	return *this;
}
CDate& CDate::operator-=(unsigned days)
{
	if (!IsDataValid(m_daysAfter1970 - days))
	{
		throw std::out_of_range("Your data out of range. Correct range is 1/1/1970 - 31.12.9999.");
	}

	m_daysAfter1970 -= days;
	return *this;
}

bool CDate::operator==(CDate const& other) const noexcept
{
	return m_daysAfter1970 == other.m_daysAfter1970;
}
bool CDate::operator!=(CDate const& other) const noexcept
{
	return m_daysAfter1970 != other.m_daysAfter1970;
}
bool CDate::operator>(CDate const& other) const noexcept
{
	return m_daysAfter1970 > other.m_daysAfter1970;
}
bool CDate::operator<(CDate const& other) const noexcept
{
	return m_daysAfter1970 < other.m_daysAfter1970;
}
bool CDate::operator<=(CDate const& other) const noexcept
{
	return m_daysAfter1970 <= other.m_daysAfter1970;
}
bool CDate::operator>=(CDate const& other) const noexcept
{
	return m_daysAfter1970 >= other.m_daysAfter1970;
}

unsigned CDate::GetShiftedMonthPositionFrom(Month const& normalMonth) const noexcept
{
	//        ____________________________________________________
	//input  |  1 |  2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
	//output | 10 | 11 | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7  |  8 |  9 |
	//        ----------------------------------------------------
	return (ToInt(normalMonth) + 9) % 12;
}
unsigned CDate::GetDaysOfYearByMonthPosition(unsigned monthPosition) const noexcept
{
	return (306 * monthPosition + 4) / 10;
}
unsigned CDate::GetMonthPositionByDayOfYear(unsigned dayOfYear) const noexcept
{
	return (10 * dayOfYear + 4) / 306;
}

bool CDate::IsDataValid(unsigned day, Month month, unsigned year) const noexcept
{
	return (year >= 1970 && year <= 9999)
		&& (static_cast<int>(month) >= 1) && (static_cast<int>(month) <= 12)
		&& (day >= 1 && day <= 31);
}
bool CDate::IsDataValid(unsigned daysAfter1970) const noexcept
{
	return (daysAfter1970 >= 0) && (daysAfter1970 <= MAX_DAYS_AFTER_1970);
}

std::istream& operator>>(std::istream& in, CDate& date)
{
	throw std::exception("");
	// TODO: вставьте здесь оператор return
}

std::ostream& operator<<(std::ostream& out, CDate date)
{
	out << date.GetDay() << "." << static_cast<int>(date.GetMonth()) << "." << date.GetYear();
	return out;
}
