#include "SnakeController.h"


//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

void SnakeController::control(Snake& snake, const std::string& input)
{
	if (input == "w")
	{
		snake.changeDirection(Direction::UP);
	}
	else if (input == "a")
	{
		snake.changeDirection(Direction::LEFT);
	}
	else if (input == "s")
	{
		snake.changeDirection(Direction::DOWN);
	}
	else if (input == "d")
	{
		snake.changeDirection(Direction::RIGHT);
	}
}
