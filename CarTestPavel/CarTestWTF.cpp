#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Car/Car.h"

//Пример Алексея
// void RequireCCarToFail(const CCar& car, const std::function<bool(CCar&)>& action)
//{
//	CCar carCopy(car);
//	REQUIRE(!action(carCopy));
//	REQUIRE(carCopy.GetDirection() == car.GetDirection());
//	// аналогично проверяем другие свойства
// }
//
// void RequireCCarToSucceed(CCar& car, const std::function<bool(CCar&)>& action, bool expectToBeTurnedOn, int expectedGear, int expectedSpeed)
//{
//	REQUIRE(action(car));
// }

SCENARIO("Движение задним ходом")
{
	//{
	//	CCar car;
	//	car.TurnOnEngine();
	//	car.SetGear(Gear::FIRST);
	//	car.SetSpeed(20);
	//	RequireCCarToFail(car, [](CCar& car) { return car.SetGear(Gear::FIRST); });
	//}

	GIVEN("A moving car with turned on engine at backward gear")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(15);
		WHEN("Setting speed in range 0-20")
		{
			car.SetSpeed(20);
			THEN("CCar changes its speed")
			{
				CHECK(car.GetSpeed() == 20);
			}
		}
	}
}
//Пример Алексея

SCENARIO("1. Проверка метода TurnOnEngine()")
{
	SECTION("1.1 Возвращает true, если двигатель включился")
	{
		CCar car;

		WHEN("двигатель включился")
		{
			bool result = car.TurnOnEngine();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}
	}

	SECTION("1.2 Возвращает true, если уже был включен.")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("двигатель включается, во включенном состоянии")
		{
			bool result = car.TurnOnEngine();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}
		}
	}

	SECTION("1.3 После включения двигателя, машина находится на нейтральной передаче, в состоянии покоя, скорость 0,")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("двигатель включается")
		{
			bool state = car.IsTurnedOn();
			Direction direction = car.GetDirection();
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("состояние двигателя - включено")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}

			THEN("машина находится в состоянии покоя")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}

			THEN("машина находится на нейтрали")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("скорость 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("2. Проверка метода TurnOffEngine()")
{

	SECTION("2.1 Выключить двигатель, если он включен и текущая передача – нейтральная, а автомобиль стоит, Скорость  равна нулю - вернется true")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("выключаю двигатель")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("2.2 состояния двигателя выключено")
			{
				bool expectedResult = false;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.3 Выключить двигатель, если он уже выключен")
	{
		CCar car;

		WHEN("выключаю двигатель")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("состояния двигателя выключено")
			{
				bool expectedResult = false;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.4 Выключить двигатель, если передача задняя")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("выключаю двигатель")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("состояния двигателя включено")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.5 Выключить двигатель, если передача первая")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("выключаю двигатель")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("состояния двигателя включено")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}
		}
	}

	SECTION("2.6 Выключить двигатель, если передача нейтральная и скорость ненулевая")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(1);
		car.SetGear(Gear::NEUTRAL);

		WHEN("выключаю двигатель")
		{
			bool result = car.TurnOffEngine();
			bool state = car.IsTurnedOn();
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("состояния двигателя включено")
			{
				bool expectedResult = true;
				REQUIRE(state == expectedResult);
			}

			THEN("скорость равна заданному значению")
			{
				int expectedResult = 1;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("3 Проверка SetGear() и SetSpeed() - При вЫключенном двигателе")
{
	SECTION("3.1 При выключенном двигателе включается только нейтраль")
	{
		CCar car;

		WHEN("включаю нейтраль")
		{
			bool result = car.SetGear(Gear::NEUTRAL);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("3.2 При вЫключенном двигателе задняя передача (-1) не включается")
	{
		CCar car;

		WHEN("включаю заднюю передачу")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("3.3 При вЫключенном двигателе первая передача не включается")
	{
		CCar car;

		WHEN("включаю первую передачу")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("3.4 При вЫключенном двигателе отрицательная скорость не выставляется")
	{
		CCar car;

		WHEN("выставляю скорость меньше нуля")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость на нуле")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("3.5 При вЫключенном двигателе скорость не выставляется")
	{
		CCar car;

		WHEN("выставляю скорость больше нуля")
		{
			bool result = car.SetSpeed(1);
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость на нуле")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("4.1 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Задняя передача")
{
	SECTION("4.1.1 На задний ход (-1) можно переключиться на нулевой скорости")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("включаю заднюю передачу")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена задняя скорость")
			{
				int expectedResult = -1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.1.2 Можно стоять на месте задав скорость 0, направление будет stop")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("задаю скорость 0")
		{
			bool result = car.SetSpeed(0);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость равна 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина стоит на месте")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.3 Можно развить скорость 1, направление будет back")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("задаю скорость 1")
		{
			bool result = car.SetSpeed(1);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость равна 1")
			{
				int expectedResult = 1;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина двигается назад")
			{
				Direction expectedResult = Direction::BACK;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.4 Можно развить скорость 20, направление будет back")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("задаю скорость 20")
		{
			bool result = car.SetSpeed(20);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость равна 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина двигается назад")
			{
				Direction expectedResult = Direction::BACK;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.5 При движении назад на нейтральной передаче не допускается включать заднюю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);
		car.SetGear(Gear::NEUTRAL);

		WHEN("включаю заднюю передачу")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("скорость равна 10")
			{
				int expectedResult = 10;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина двигается назад")
			{
				Direction expectedResult = Direction::BACK;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.1.6 Переключившись на заднем ходу на нейтральную передачу на ненулевой скорости, скорость можно уменьшать")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);
		car.SetGear(Gear::NEUTRAL);

		WHEN("уменьшаю скорость")
		{
			bool result = car.SetSpeed(8);
			int speed = car.GetSpeed();

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость равна 8")
			{
				int expectedResult = 8;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.1.7 Переключившись на заднем ходу на нейтральную передачу на ненулевой скорости переключиться на переднюю передачу можно только после остановки")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);
		car.SetGear(Gear::NEUTRAL);
		car.SetSpeed(0);

		WHEN("включаю первую скорость")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("Включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.1[Негативный сценарий 1] Нельзя развить скорость меньше 0 ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("задаю отрицательную скорость")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.1[Негативный сценарий 2] Нельзя развить скорость больше 20 ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);

		WHEN("задаю скорость больше 20")
		{
			bool result = car.SetSpeed(21);
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.1[Негативный сценарий 3] Переключившись на заднем ходу на нейтральную передачу на ненулевой скорости переключиться на переднюю нельзя")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(15);
		car.SetGear(Gear::NEUTRAL);

		WHEN("задаю первую передачу")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("Включена нейтральная передача")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.1[Негативный сценарий 4] Переключившись на заднем ходу на нейтральную передачу на ненулевой скорости, скорость нельзя увеличить")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(10);
		car.SetGear(Gear::NEUTRAL);

		WHEN("увеличиваю скорость")
		{
			bool result = car.SetSpeed(15);
			int speed = car.GetSpeed();

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость остается неизменной")
			{
				int expectedResult = 10;
				REQUIRE(speed == expectedResult);
			}
		}
	}
	/*
	SECTION("4.1[Негативный сценарий 5] Нельзя задавать скорость меньше -1")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::REVERSE);
		car.SetSpeed(20);

		WHEN("увеличиваю скорость")
		{
			bool result = car.SetGear(-2);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод возвращает false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("передача заняя")
			{
				int expectedResult = -1;
				REQUIRE(gear == expectedResult);
			}
		}
	}
	*/
}

SCENARIO("4.2 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Нейтраль")
{
	SECTION("4.2.1 На нейтрали можно переключиться на нейтраль")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("включаю нейтраль")
		{
			bool result = car.SetGear(Gear::NEUTRAL);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод возвращает true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.2.2 Переключиться на нейтраль с 1й скорости и остановиться")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(15);

		WHEN("включаю нейтраль и останавливаюсь")
		{
			car.SetGear(Gear::NEUTRAL);
			car.SetSpeed(0);

			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("скорость 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина стоит на месте")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.2.7 При ненулевой скорости при движении прямо нельяз включить заднюю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(15);
		car.SetGear(Gear::NEUTRAL);

		WHEN("включаю заднюю передачу")
		{
			car.SetGear(Gear::REVERSE);

			int gear = static_cast<int>(car.GetGear());
			Direction direction = car.GetDirection();

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}

			THEN("машина двигается вперед")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}
}

SCENARIO("4.3 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Первая передача(1) - скорость 0 – 30")
{
	SECTION("4.3.1 Можно стоять на месте задав скорость 0, направление будет stop")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("задаю скорость 0")
		{
			bool result = car.SetSpeed(0);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина стоит на месте")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.3.2 Можно развить скорость 1, направление будет forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("задаю скорость 1")
		{
			bool result = car.SetSpeed(1);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 1")
			{
				int expectedResult = 1;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина двигается вперед")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.3.3 На нулевой скорости можно включить заднюю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("включаю заднюю передачу")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена задняя передача")
			{
				int expectedResult = -1;
				REQUIRE(gear == expectedResult);
			}

			THEN("машина стоит на месте")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.3.4 Можно развить скорость 30")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("задаю скорость 30")
		{
			bool result = car.SetSpeed(30);
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 30")
			{
				int expectedResult = 30;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3.5 При скорости 30 можно переключиться с 3й на 1ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);

		WHEN("включить первую передачу")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3.6 При скорости 20 можно переключиться с 2й на 1ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(20);

		WHEN("включить первую передачу")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3.7 На нейтрали можно уменьшить скорость с 30 до 20")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::NEUTRAL);

		WHEN("уменьшить скорость до 20")
		{
			bool result = car.SetSpeed(20);
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3.8 На нейтрали нельзя увеличить скорость")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::NEUTRAL);

		WHEN("увеличить скорость до 25")
		{
			bool result = car.SetSpeed(25);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3.9 На первой скорости можно остановиться")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);

		WHEN("останавливаюсь")
		{
			bool result = car.SetSpeed(0);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 0")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина стоит на месте")
			{
				Direction expectedResult = Direction::STILL;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.3.10 На нейтрали уменьшить скорость со 40 до 20 и переключиться на 1ю")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::NEUTRAL);
		car.SetSpeed(20);

		WHEN("Уменьшить скорость")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передавча")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3.11 На скорости можно переключиться с нейтрали на 1ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::NEUTRAL);

		WHEN("включить превую передачу")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3[Негативный сценарий 1] Нельзя развить скорость меньше 0")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("задать скорость меньше 0")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("останется нулевая скорость")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3[Негативный сценарий 2] Нельзя развить скорость меньше больше 30")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);

		WHEN("задать скорость больше 30")
		{
			bool result = car.SetSpeed(31);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("останется нулевая скорость")
			{
				int expectedResult = 0;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.3[Негативный сценарий 3] Нельзя переключиться на заднюю передачу (-1) на ненулевой скорости")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(10);

		WHEN("переключиться на заднюю передачу")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.3[Негативный сценарий 4] При скорости 31 нельзя переключиться со 2й на 1ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(31);

		WHEN("переключиться со 2й на 1ю передачу")
		{
			bool result = car.SetGear(Gear::FIRST);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}
}

SCENARIO("4.4 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Вторая передача (2) - скорость 20 – 50")
{
	SECTION("4.4.1 При скорости 20 можно переключиться с 1й на 2ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);

		WHEN("переключиться со 1й на 2ю передачу")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.2 При скорости 30 можно переключиться с 1й на 2ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);

		WHEN("переключиться со 1й на 2ю передачу")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.3 При скорости 30 можно переключиться с 3й на 2ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);

		WHEN("переключиться со 3й на 2ю передачу")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.4 При скорости 50 можно переключиться с 3й на 2ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);

		WHEN("переключиться со 3й на 2ю передачу")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.5 При скорости 40 можно переключиться с 4й на 2ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(40);
		car.SetGear(Gear::FOURTH);

		WHEN("переключиться со 4й на 2ю передачу")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.6 При скорости 50 можно переключиться с 5й на 2ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FIFTH);

		WHEN("переключиться со 5й на 2ю передачу")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.7 Можно переключиться со второй на вторую передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);

		WHEN("переключиться на 2ю передачу")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.8 Можно развить скорость 20 направление будет forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);

		WHEN("уменьшить скорость до 20")
		{
			bool result = car.SetSpeed(20);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 20")
			{
				int expectedResult = 20;
				REQUIRE(speed == expectedResult);
			}

			THEN("движение вперед")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.4.9 Можно развить скорость 50 направление будет forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);

		WHEN("увеличить скорость до 50")
		{
			bool result = car.SetSpeed(50);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 50")
			{
				int expectedResult = 50;
				REQUIRE(speed == expectedResult);
			}

			THEN("движение вперед")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.4.10 Можно переключиться на нейтраль")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);

		WHEN("включить нейтраль")
		{
			bool result = car.SetGear(Gear::NEUTRAL);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.11 Можно переключиться с нейтрали на 2ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetGear(Gear::NEUTRAL);

		WHEN("включить вторую передачу")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая передача")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4.12 На нейтрали можно уменьшить скорость")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::NEUTRAL);

		WHEN("уменьшить скорость")
		{
			bool result = car.SetSpeed(25);
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 25")
			{
				int expectedResult = 25;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4.13 На нейтрали нельзя увеличить скорость")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::NEUTRAL);

		WHEN("увеличить скорость")
		{
			bool result = car.SetSpeed(45);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 1] При нулевой передаче и нулевой скорости нельзя включить 2ю передачу")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("включить вторую передачу")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 2] Со второй передачи нельзя переключиться на заднюю передачу (-1)")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(25);
		car.SetGear(Gear::SECOND);

		WHEN("включить заднюю передачу")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена вторая скорость")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 3] На второй передаче нельзя развить скорость меньше 20")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(25);
		car.SetGear(Gear::SECOND);

		WHEN("уменьшить скорость до 19")
		{
			bool result = car.SetSpeed(19);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 25")
			{
				int expectedResult = 25;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 4] На второй передаче нельзя развить скорость больше 50")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(25);
		car.SetGear(Gear::SECOND);

		WHEN("увеличить скорость до 51")
		{
			bool result = car.SetSpeed(51);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 25")
			{
				int expectedResult = 25;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 5] При скорости 19 нельзя переключиться с 1й на 2ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(19);

		WHEN("переключить передачу на вторую")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 1;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.4[Негативный сценарий 6] При скорости 51 нельзя переключиться с 3й на 2ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(51);

		WHEN("переключить передачу на вторую")
		{
			bool result = car.SetGear(Gear::SECOND);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена первая передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}
}

SCENARIO("4.5 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Третья передача (3) - скорость 30 – 60")
{
	SECTION("4.5.1 При скорости 30 можно переключиться с 1й на 3ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);

		WHEN("переключиться со 1й на 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 3я передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.3 При скорости 50 со 2й передачи можно переключиться на 3ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(50);

		WHEN("переключиться со 2й на 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 3я передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.4 При скорости 40 с 4й передачи можно переключиться на 3ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::FOURTH);

		WHEN("переключиться с 4й на 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 3я передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.5 При скорости 60 с 4й передачи можно переключиться на 3ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::FOURTH);
		car.SetSpeed(60);

		WHEN("переключиться с 4й на 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 3я передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}

			THEN("скорость 60")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5.6 При скорости 50 со 5й передачи можно переключиться на 3ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(50);
		car.SetGear(Gear::FIFTH);

		WHEN("переключиться с 5й на 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 3я передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}

			THEN("скорость 50")
			{
				int expectedResult = 50;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5.7 При скорости 60 со 5й передачи можно переключиться на 3ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(50);
		car.SetGear(Gear::FIFTH);
		car.SetSpeed(60);

		WHEN("переключиться с 5й на 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 3я передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}

			THEN("заданная скорость")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5.8 На 3й передаче можно переключиться на 3ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);

		WHEN("переключиться на 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 3я передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}

			THEN("заданная скорость")
			{
				int expectedResult = 30;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5.9 Можно развить скорость 30 направление будет forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);

		WHEN("уменьшить скорость")
		{
			bool result = car.SetSpeed(30);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 30")
			{
				int expectedResult = 30;
				REQUIRE(speed == expectedResult);
			}

			THEN("движение вперед")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.5.10 Можно развить скорость 60 направление будет forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);

		WHEN("Увеличить скорость")
		{
			bool result = car.SetSpeed(60);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 60")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}

			THEN("движение вперед")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.5.11 Можно переключиться на нейтраль ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);

		WHEN("переключиться на нейтраль")
		{
			bool result = car.SetGear(Gear::NEUTRAL);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 45")
			{
				int expectedResult = 45;
				REQUIRE(speed == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.12 Можно переключиться с нейтрали на 3ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);
		car.SetGear(Gear::NEUTRAL);

		WHEN("переключиться на 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 45")
			{
				int expectedResult = 45;
				REQUIRE(speed == expectedResult);
			}

			THEN("включена 3я передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.13 На нейтрали можно уменьшить скорость")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);
		car.SetGear(Gear::NEUTRAL);

		WHEN("уменьшить скорость")
		{
			bool result = car.SetSpeed(40);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.14 На нейтрали нельзя увеличить скорость")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(45);
		car.SetGear(Gear::NEUTRAL);

		WHEN("уменьшить скорость")
		{
			bool result = car.SetSpeed(50);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 45")
			{
				int expectedResult = 45;
				REQUIRE(speed == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5.15 На нейтрали уменьшить скорость со 70 до 50 и переключиться на 3ю")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(50);
		car.SetGear(Gear::FIFTH);
		car.SetSpeed(70);
		car.SetGear(Gear::NEUTRAL);

		WHEN("уменьшить скорость  и включить 3ю передачу")
		{
			car.SetSpeed(50);
			car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());
			int speed = car.GetSpeed();

			THEN("скорость 50")
			{
				int expectedResult = 50;
				REQUIRE(speed == expectedResult);
			}

			THEN("включена 3я скорость")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5 [Негативный сценарий 1] При нулевой передаче и нулевой скорости нельзя включить 3ю передачу")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("переключиться на 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтраль")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5 [Негативный сценарий 2] На 3й передаче нельзя переключиться на заднюю передачу (-1)")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);

		WHEN("переключиться на заднюю передачу")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 3я скорость")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5 [Негативный сценарий 3] При скорости 29 нельзя переключиться с 2й на 3ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(29);
		car.SetGear(Gear::SECOND);

		WHEN("включить 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 2я скорость")
			{
				int expectedResult = 2;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5 [Негативный сценарий 4] При скорости 61 нельзя переключиться с 4й на 3ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::FOURTH);
		car.SetSpeed(61);

		WHEN("включить 3ю передачу")
		{
			bool result = car.SetGear(Gear::THIRD);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 4я передача")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.5 [Негативный сценарий 7] Нельзя развить отрицательную скорость")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::THIRD);

		WHEN("задать отрицательную скорость")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5 [Негативный сценарий 8] Нельзя развить скорость 29")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::THIRD);

		WHEN("задать скорость 29")
		{
			bool result = car.SetSpeed(29);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.5 [Негативный сценарий 9] Нельзя развить скорость 61")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(20);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);
		car.SetGear(Gear::THIRD);

		WHEN("задать скорость 61")
		{
			bool result = car.SetSpeed(61);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}

SCENARIO("4.6 Проверка SetGear() и SetSpeed() - При вКлюченном двигателе - Четвертая передача (4) - скорость 40 – 90")
{
	SECTION("4.6.1 При скорости 40 со 2й передачи можно переключиться на 4ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::SECOND);
		car.SetSpeed(40);

		WHEN("переключиться на 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 4я передача")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.2 При скорости 40 с 3й передачи можно переключиться на 4ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(40);

		WHEN("переключиться на 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 4я передача")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.3 При скорости 60 с 3й передачи можно переключиться на 4ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);

		WHEN("переключиться на 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 4я передача")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.4 При скорости 50 с 5й передачи можно переключиться на 4ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FIFTH);

		WHEN("переключиться на 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 4я передача")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.5 При скорости 60 с 5й передачи можно переключиться на 4ю передачу ")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::FIFTH);

		WHEN("переключиться на 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 4я передача")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.7 С 4й передачи можно переключиться на 4ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);

		WHEN("переключиться на 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 4я передача")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.8 Можно развить скорость 40 направление будет forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);

		WHEN("задать скорость 40")
		{
			bool result = car.SetSpeed(40);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 40")
			{
				int expectedResult = 40;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина двигается вперед")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.6.9 Можно развить скорость 90 направление будет forward")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);

		WHEN("задать скорость 90")
		{
			bool result = car.SetSpeed(90);
			int speed = car.GetSpeed();
			Direction direction = car.GetDirection();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 40")
			{
				int expectedResult = 90;
				REQUIRE(speed == expectedResult);
			}

			THEN("машина двигается вперед")
			{
				Direction expectedResult = Direction::FORWARD;
				REQUIRE(direction == expectedResult);
			}
		}
	}

	SECTION("4.6.11 Можно переключиться с нейтрали на 4ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::NEUTRAL);

		WHEN("переключиться на 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 4я передача")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6.13 На нейтрали можно уменьшить скорость")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);
		car.SetSpeed(90);
		car.SetGear(Gear::NEUTRAL);

		WHEN("уменьшить скорость до 50")
		{
			bool result = car.SetSpeed(50);
			int speed = car.GetSpeed();

			THEN("метод вернет true")
			{
				bool expectedResult = true;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость уменьшена до 50")
			{
				int expectedResult = 50;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.6.14 На нейтрали нельзя увеличить скорость")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);
		car.SetSpeed(80);
		car.SetGear(Gear::NEUTRAL);

		WHEN("увеличить скорость на 5")
		{
			bool result = car.SetSpeed(85);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость осталась прежней")
			{
				int expectedResult = 80;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.6 [Негативный сценарий 1] При нулевой передаче и нулевой скорости нельзя включить 4ю передачу")
	{
		CCar car;
		car.TurnOnEngine();

		WHEN("включить 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтральная передача")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6 [Негативный сценарий 2] С 4й передачи нельзя переключиться на заднюю передачу (-1)")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(50);
		car.SetGear(Gear::FOURTH);

		WHEN("включить заднюю передачу")
		{
			bool result = car.SetGear(Gear::REVERSE);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 4я передача")
			{
				int expectedResult = 4;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6 [Негативный сценарий 3] При скорости 39 нельзя переключиться с 3й на 4ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(39);

		WHEN("включить 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 3я передача")
			{
				int expectedResult = 3;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6 [Негативный сценарий 4] При скорости 91 нельзя переключиться с 5й на 4ю передачу")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::FIFTH);
		car.SetSpeed(91);

		WHEN("включить 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена 5я передача")
			{
				int expectedResult = 5;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6 [Негативный сценарий 5] На нейтрали уменьшить скорость до 39 и переключиться на 4ю")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::NEUTRAL);
		car.SetSpeed(39);

		WHEN("включить 4ю передачу")
		{
			bool result = car.SetGear(Gear::FOURTH);
			int gear = static_cast<int>(car.GetGear());

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("включена нейтральная передача")
			{
				int expectedResult = 0;
				REQUIRE(gear == expectedResult);
			}
		}
	}

	SECTION("4.6 [Негативный сценарий 7] Нельзя развить отрицательную скорость")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::FOURTH);

		WHEN("задать отрицательную скорость")
		{
			bool result = car.SetSpeed(-1);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 60")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.6 [Негативный сценарий 8] Нельзя развить скорость 39")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::FOURTH);

		WHEN("задать скорость 39")
		{
			bool result = car.SetSpeed(39);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 60")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}
		}
	}

	SECTION("4.6 [Негативный сценарий 9] Нельзя развить скорость 91")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(Gear::FIRST);
		car.SetSpeed(30);
		car.SetGear(Gear::THIRD);
		car.SetSpeed(60);
		car.SetGear(Gear::FOURTH);

		WHEN("задать скорость 91")
		{
			bool result = car.SetSpeed(91);
			int speed = car.GetSpeed();

			THEN("метод вернет false")
			{
				bool expectedResult = false;
				REQUIRE(result == expectedResult);
			}

			THEN("скорость 60")
			{
				int expectedResult = 60;
				REQUIRE(speed == expectedResult);
			}
		}
	}
}
