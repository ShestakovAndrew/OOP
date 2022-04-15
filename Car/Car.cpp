#include "Car.h"
#include <iostream>

namespace
{
	bool GearExist(Gear const& gear)
	{
		return (gear <= Gear::FIFTH) and (gear >= Gear::REVERSE);
	}

	bool SpeedInRange(Gear const& gear, int speed)
	{
		SpeedRange speadRangeByGear = GEAR_SPEED_RANGES.find(gear)->second;
		return (speed >= speadRangeByGear.lowerBound and speed <= speadRangeByGear.upperBound);
	}

	bool CheakReverseGear(Gear gear, int speed)
	{
		return (gear != Gear::REVERSE) or (speed == 0);
	}

	bool CheckBackDirection(Direction const& currentDirection, Gear const& gear, Gear const& m_gear)
	{
		if ((currentDirection == Direction::BACK) and	
			(gear == Gear::FIRST) and	
			(m_gear == Gear::NEUTRAL))
		{
			return false;
		}
		return true;
	}

	bool CheckForwardDirection(Direction const& currentDirection, Gear const& gear, Gear const& m_gear)
	{
		if ((currentDirection != Direction::FORWARD) and
			(gear != Gear::NEUTRAL) and
			(m_gear == Gear::REVERSE))
		{
			return false;
		}
		return true;
	}

	bool GearCanBeSwitch(Direction const& currentDirection, Gear const& gear, int speed, Gear const& m_gear)
	{
		return CheakReverseGear(gear, speed) and
			CheckForwardDirection(currentDirection, gear, m_gear) and
			CheckBackDirection(currentDirection, gear, m_gear);
	}

	bool ÑarMovingBackward(Gear const& gear, int speed)
	{
		return (gear == Gear::REVERSE) or (speed < 0);
	}

	bool CanChangeSpeedInNeutralGear(Gear const& gear, int speed, int m_speed)
	{
		return (gear != Gear::NEUTRAL) or ((gear == Gear::NEUTRAL) and (speed < m_speed));
	}
}

bool CCar::IsTurnedOn() const
{
	return m_turnedOn;
}

Direction CCar::GetDirection() const
{
	if (m_speed < 0) return Direction::BACK;
	else if (m_speed > 0) return Direction::FORWARD;
	else return Direction::STILL;
}

Gear CCar::GetGear() const
{
	return m_gear;
}

int CCar::GetSpeed() const
{
	return std::abs(m_speed);
}

bool CCar::TurnOnEngine()
{
	m_turnedOn = true;
	return true;
}

bool CCar::TurnOffEngine()
{
	if ((m_turnedOn and (m_gear == Gear::NEUTRAL) and (m_speed == 0)) or !m_turnedOn)
	{
		m_turnedOn = false;
		return true;
	}
	return false;
}

bool CCar::SetGear(Gear const& gear)
{
	if ((!m_turnedOn and gear == Gear::NEUTRAL) or
		m_turnedOn and 
		GearExist(gear) and 
		SpeedInRange(gear, GetSpeed()) and
		GearCanBeSwitch(GetDirection(), gear, m_speed, m_gear))
	{
		m_gear = gear;
		return true;
	}

	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (SpeedInRange(m_gear, speed) and CanChangeSpeedInNeutralGear(m_gear, speed, GetSpeed()))
	{
		m_speed = ÑarMovingBackward(m_gear, m_speed) ? -speed : speed;
		return true;
	}

	return false;
}