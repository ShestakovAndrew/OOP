#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <algorithm>
#include "Car/Car.h"

namespace
{
	std::vector<Gear> gears { 
		Gear::FIRST ,
		Gear::SECOND,
		Gear::THIRD,
		Gear::FOURTH,
		Gear::FIFTH 
	};

	bool SpeedWithinGearRestriction(Gear const& gear, int speed)
	{
		SpeedRange speadRangeByGear = GEAR_SPEED_RANGES.find(gear)->second;
		return ((speed >= speadRangeByGear.lowerBound) and speed <= (speadRangeByGear.upperBound));
	}

	void GearShiftTest(CCar& car, int speed)
	{
		car.SetSpeed(speed);

		for (Gear gear : gears)
		{
			if (SpeedWithinGearRestriction(gear, speed))
			{
				REQUIRE(car.SetGear(gear));
			}
			else
			{
				REQUIRE_FALSE(car.SetGear(gear));
			}
		}
	}

	void TestCarCanSetSpeed(CCar& car, int speed)
	{
		REQUIRE(car.SetSpeed(speed));
		REQUIRE(car.GetSpeed() == speed);
	}

	void TestCarFailsToSetSpeed(CCar& car, int setSpeed, int currentSpeed)
	{
		REQUIRE_FALSE(car.SetSpeed(setSpeed));
		REQUIRE(car.GetSpeed() == currentSpeed);
	}

	void TestCarCanSetGear(CCar& car, Gear const& gear)
	{
		REQUIRE(car.SetGear(gear));
		REQUIRE(car.GetGear() == gear);
	}

	void TestCarFailsToSetGear(CCar& car, Gear const& setGear, Gear const& currentGear)
	{
		REQUIRE_FALSE(car.SetGear(setGear));
		REQUIRE(car.GetGear() == currentGear);
	}
}

TEST_CASE("TestCarCreation")
{
	CCar validCar;

	REQUIRE_FALSE(validCar.IsTurnedOn());
	REQUIRE(validCar.GetSpeed() == 0);
	REQUIRE(validCar.GetGear() == Gear::NEUTRAL);
	REQUIRE(validCar.GetDirection() == Direction::STILL);
}

TEST_CASE("TestEngineOnOff")
{
	CCar someCar;

	SECTION("Engine should be on")
	{
		REQUIRE(someCar.TurnOnEngine());
		REQUIRE(someCar.IsTurnedOn());
	}
	
	SECTION("Engine should be off if this posible")
	{
		REQUIRE(someCar.TurnOffEngine()); 
		someCar.TurnOnEngine();
		someCar.SetGear(Gear::FIRST);
		REQUIRE(someCar.SetSpeed(1));

		REQUIRE_FALSE(someCar.TurnOffEngine()); //скорость должна равняться 0 
		someCar.SetSpeed(0);
		REQUIRE_FALSE(someCar.TurnOffEngine()); //передача должна быть нейтральная
		someCar.SetGear(Gear::NEUTRAL);
		REQUIRE(someCar.TurnOffEngine()); //только теперь можно выключить двигатель.
		REQUIRE_FALSE(someCar.IsTurnedOn());
	}
}

TEST_CASE("TestGearShift")
{
	// создаем машину
	CCar car;
	car.TurnOnEngine();

	SECTION("Switching gear if engine turn off")
	{
		car.TurnOffEngine();
		TestCarCanSetGear(car, Gear::NEUTRAL);
	}

	// проверка переключений передачи при увеличении скорости
	WHEN("Switching gear at increase in speed")
	{
		car.TurnOnEngine();
		REQUIRE(car.SetGear(Gear::FIRST));

		for (int speed = 0; speed <= 150; speed += 1)
		{
			GearShiftTest(car, speed);
		}

		// проверка переключения передачи при уменьшении скорости
		THEN("Switching gear at decrease in speed")
		{
			std::reverse(gears.begin(), gears.end());

			for (int speed = 50; speed >= 0; speed -= 1)
			{
				GearShiftTest(car, speed);
			}
		}
	}

	// проверка переключения передачи на задний ход и на нейтраль.
	SECTION("Gear shifting to reverse and neutral")
	{
		TestCarCanSetGear(car, Gear::REVERSE);

		car.SetSpeed(10);
		TestCarCanSetGear(car, Gear::NEUTRAL);
		TestCarFailsToSetGear(car, Gear::FIRST, Gear::NEUTRAL);

		car.SetSpeed(0);
		TestCarCanSetGear(car, Gear::FIRST);
	}
}

TEST_CASE("TestSpeedChanges")
{
	CCar car;
	car.TurnOnEngine();

	//передняя передача
	SECTION("Forward gear") 
	{
		car.SetGear(Gear::FIRST);
		TestCarFailsToSetSpeed(car, -1, 0);
		TestCarCanSetSpeed(car, 0);
		TestCarCanSetSpeed(car, 1);
		TestCarCanSetSpeed(car, 30);
		TestCarFailsToSetSpeed(car, 31, 30);

		car.SetGear(Gear::SECOND);
		TestCarFailsToSetSpeed(car, 19, 30);
		TestCarCanSetSpeed(car, 20);
		TestCarCanSetSpeed(car, 50);
		TestCarFailsToSetSpeed(car, 51, 50);

		car.SetGear(Gear::THIRD);
		TestCarFailsToSetSpeed(car, 29, 50);
		TestCarCanSetSpeed(car, 30);
		TestCarCanSetSpeed(car, 60);
		TestCarFailsToSetSpeed(car, 61, 60);

		car.SetGear(Gear::FOURTH);
		TestCarFailsToSetSpeed(car, 39, 60);
		TestCarCanSetSpeed(car, 40);
		TestCarCanSetSpeed(car, 90);
		TestCarFailsToSetSpeed(car, 91, 90);

		car.SetGear(Gear::FIFTH);
		TestCarFailsToSetSpeed(car, 49, 90);
		TestCarCanSetSpeed(car, 50);
		TestCarCanSetSpeed(car, 150);
		TestCarFailsToSetSpeed(car, 151, 150);

		car.SetGear(Gear::NEUTRAL);
		TestCarCanSetSpeed(car, 149);
		TestCarFailsToSetSpeed(car, 150, 149);
		TestCarCanSetSpeed(car, 0);
		TestCarFailsToSetSpeed(car, 1, 0);
	}

	CCar anotherCar;
	anotherCar.TurnOnEngine();

	//задняя передача
	SECTION("Reverse gear") 
	{
		anotherCar.SetGear(Gear::REVERSE);
		TestCarCanSetSpeed(anotherCar, 20);
		TestCarFailsToSetSpeed(anotherCar, 21, 20);
		TestCarCanSetSpeed(anotherCar, 0);
	}
}

TEST_CASE("TestCarDirection")
{
	CCar car;
	REQUIRE(car.GetDirection() == Direction::STILL);

	car.TurnOnEngine();
	REQUIRE(car.GetDirection() == Direction::STILL);

	car.SetGear(Gear::FIRST);
	REQUIRE(car.GetDirection() == Direction::STILL);

	car.SetSpeed(15);
	REQUIRE(car.GetDirection() == Direction::FORWARD);

	car.SetGear(Gear::NEUTRAL);
	REQUIRE(car.GetDirection() == Direction::FORWARD);

	car.SetSpeed(0);
	REQUIRE(car.GetDirection() == Direction::STILL);

	car.SetGear(Gear::REVERSE);
	REQUIRE(car.GetDirection() == Direction::STILL);

	car.SetSpeed(10);
	REQUIRE(car.GetDirection() == Direction::BACK);

	car.SetGear(Gear::NEUTRAL);
	REQUIRE(car.GetDirection() == Direction::BACK);

	car.SetSpeed(0);
	REQUIRE(car.GetDirection() == Direction::STILL);

	car.SetGear(Gear::FIRST);
	car.SetSpeed(30);
	REQUIRE(car.GetDirection() == Direction::FORWARD);
}
