#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Car/Car.h"
#include "Car/Driver.h"
#include <sstream>

namespace
{
	void VerifyCommandHandling(std::string const& command, std::string const& expectedResult, CCar& car)
	{
		std::stringstream input, output;
		CDriver driver(car, input, output);
		input << command;
		REQUIRE(driver.HandleCommand());
		REQUIRE(expectedResult == output.str());
	}
}

TEST_CASE("Handle command EngineOn must return behavior")
{
	CCar car;
	VerifyCommandHandling("EngineOn", "Car has been turned on.\n", car);
	VerifyCommandHandling("EngineOn", "Car is already turned on.\n", car);
	VerifyCommandHandling("EngineOn", "Car is already turned on.\n", car);
}

TEST_CASE("Handle command EngineOff must return behavior")
{
	CCar car;

	car.TurnOnEngine();
	car.SetGear(Gear::FIRST);
	car.SetSpeed(10);
	VerifyCommandHandling("EngineOff", "Car has not been turned off.\n", car);

	car.SetGear(Gear::NEUTRAL);
	VerifyCommandHandling("EngineOff", "Car has not been turned off.\n", car);

	car.SetGear(Gear::FIRST);
	car.SetSpeed(0);
	VerifyCommandHandling("EngineOff", "Car has not been turned off.\n", car);

	car.SetGear(Gear::NEUTRAL);
	VerifyCommandHandling("EngineOff", "Car has been turned off.\n", car);

	VerifyCommandHandling("EngineOff", "Car is already turned off.\n", car);
}

TEST_CASE("Handle command Info must return car status")
{
	CCar car;
	VerifyCommandHandling("Info", "Car is turned off\nDirection is still\nSpeed is 0\nGear is neutral\n", car);

	car.TurnOnEngine();
	VerifyCommandHandling("Info", "Car is turned on\nDirection is still\nSpeed is 0\nGear is neutral\n", car);

	car.SetGear(Gear::FIRST);
	car.SetSpeed(20);
	VerifyCommandHandling("Info", "Car is turned on\nDirection is forward\nSpeed is 20\nGear is first\n", car);

	car.SetSpeed(0);
	car.SetGear(Gear::REVERSE);
	car.SetSpeed(10);
	VerifyCommandHandling("Info", "Car is turned on\nDirection is back\nSpeed is 10\nGear is reverse\n", car);
}

TEST_CASE("Handle command SetSpeed must return behavior")
{
	CCar car;
	VerifyCommandHandling("SetSpeed 10", "Speed has not been changed.\n", car);

	car.TurnOnEngine();
	VerifyCommandHandling("SetSpeed 10", "Speed has not been changed.\n", car);

	car.SetGear(Gear::FIRST);
	VerifyCommandHandling("SetSpeed 10", "Speed has been changed.\n", car);
	VerifyCommandHandling("SetSpeed 20", "Speed has been changed.\n", car);
}

TEST_CASE("Handle command SetGear must return behavior")
{
	CCar car;
	VerifyCommandHandling("SetGear -1", "Gear has not been changed.\n", car);
	car.TurnOnEngine();
	VerifyCommandHandling("SetGear 4", "Gear has not been changed.\n", car);

	VerifyCommandHandling("SetGear -1", "Gear has been changed.\n", car);
}

TEST_CASE("If command is invalid then handle command must return false")
{
	CCar car;
	std::stringstream input, output;
	CDriver driver(car, input, output);
	input << "invalid command";
	REQUIRE(!driver.HandleCommand());
}