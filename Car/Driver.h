#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <map>

#include "Car.h"

class CDriver
{
public:

	CDriver(CCar& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:

	bool Info(std::istream& input);
	bool EngineOn(std::istream& input);
	bool EngineOff(std::istream& input);
	bool SetGear(std::istream& input);
	bool SetSpeed(std::istream& input);

private:

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	const ActionMap m_actionMap;
};

