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
	void Info(std::istream& input);
	void EngineOn(std::istream& input);
	void EngineOff(std::istream& input);
	void SetGear(std::istream& input);
	void SetSpeed(std::istream& input);

	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	using Handler = std::function<void(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	const ActionMap m_actionMap;
};

