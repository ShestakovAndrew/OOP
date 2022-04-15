#pragma once
#include <math.h>
#include <unordered_map>

enum class Direction
{
	BACK = -1,
	STILL,
	FORWARD
};

enum class Gear
{
	REVERSE = -1,
	NEUTRAL,
	FIRST,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH
};

struct SpeedRange
{
	int lowerBound;
	int upperBound;
};

const std::unordered_map<Gear, SpeedRange> GEAR_SPEED_RANGES = {
	{Gear::REVERSE, {0, 20}},
	{Gear::NEUTRAL, {0, 150}},
	{Gear::FIRST, {0, 30}},
	{Gear::SECOND, {20, 50}},
	{Gear::THIRD, {30, 60}},
	{Gear::FOURTH, {40, 90}},
	{Gear::FIFTH, {50, 150}},
};

class CCar
{
public:

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	Gear GetGear() const;
	int GetSpeed() const;

	bool TurnOnEngine();
	bool TurnOffEngine();

	bool SetGear(Gear const& gear);
	bool SetSpeed(int speed);

private:

	bool m_turnedOn = false;
	Gear m_gear = Gear::NEUTRAL;
	int m_speed = 0;
};