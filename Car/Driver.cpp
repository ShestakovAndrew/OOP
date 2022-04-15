#include "Driver.h"

namespace
{
	static const std::unordered_map<Direction, std::string> DIRECTION_TABLE =
	{
		{ Direction::BACK, "reverse" },
		{ Direction::STILL, "still" },
		{ Direction::FORWARD, "forward" }
	};

	Gear IntToGear(int gear)
	{
		return static_cast<Gear>(gear);
	}

	int GearToInt(Gear gear)
	{
		return static_cast<int>(gear);
	}
}

CDriver::CDriver(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car), m_input(input), m_output(output)
	, m_actionMap(
	{
		{ "Info", bind(&CDriver::Info, this, std::placeholders::_1) },
		{ "EngineOn", bind(&CDriver::EngineOn, this, std::placeholders::_1) },
		{ "EngineOff", bind(&CDriver::EngineOff, this, std::placeholders::_1) },
		{ "SetGear", bind(&CDriver::SetGear, this, std::placeholders::_1) },
		{ "SetSpeed", bind(&CDriver::SetSpeed, this, std::placeholders::_1) } 
	})
{

}

bool CDriver::HandleCommand()
{
	std::string command;
	std::getline(m_input, command);
	std::istringstream sstream(command);
	std::string action;
	sstream >> action;

	const auto it = m_actionMap.find(action);

	if (it != m_actionMap.end())
	{
		it->second(sstream);
		return true;
	}

	return false;
}

bool CDriver::Info(std::istream& input)
{
	std::string carCondition = m_car.IsTurnedOn() ? "on" : "off";

	try
	{
		m_output << "Car is turned " + carCondition << std::endl;
		m_output << "Direction is " << (DIRECTION_TABLE.find(m_car.GetDirection())->second) << std::endl;
		m_output << "Speed is " << m_car.GetSpeed() << std::endl;
		m_output << "Condition of gear box is " << GearToInt(m_car.GetGear()) << std::endl;
	}
	catch (const std::exception&)
	{
		return false;
	}

	return true;
}

bool CDriver::EngineOn(std::istream& input)
{
	if (!m_car.TurnOnEngine())
	{
		m_output << "Car is already turned on." << std::endl;
	}
	else
	{
		m_output << "Car has been turned on." << std::endl;
	}

	return true;
}

bool CDriver::EngineOff(std::istream& input)
{
	if ((m_car.GetGear() != Gear::NEUTRAL) or (m_car.GetSpeed() != 0))
	{
		m_output << "Car has not been turned off." << std::endl;
	}
	else if (m_car.TurnOffEngine())
	{
		m_output << "Car has been turned off." << std::endl;
	}
	else if (!m_car.TurnOffEngine())
	{
		m_output << "Car is already turned off." << std::endl;
	}
	else
	{
		m_output << "Unknown command." << std::endl;
		return false;
	}

	return true;
}

bool CDriver::SetGear(std::istream& input)
{
	if (!m_car.IsTurnedOn())
	{
		m_output << "Car has not been turned on." << std::endl;
		return false;
	}

	int gear;
	input >> gear;

	if (!m_car.SetGear(IntToGear(gear)))
	{
		m_output << "Condition of gear box has not been changed." << std::endl;
		return false;
	}
	m_output << "Condition of gear box has been changed." << std::endl;

	return true;
}

bool CDriver::SetSpeed(std::istream& input)
{
	if (!m_car.IsTurnedOn())
	{
		m_output << "Car has not been turned on." << std::endl;
		return false;
	}

	int speed;
	input >> speed;

	if (!m_car.SetSpeed(speed))
	{
		m_output << "Speed has not been changed." << std::endl;
		return false;
	}
	m_output << "Speed has been changed." << std::endl;

	return true;
}
