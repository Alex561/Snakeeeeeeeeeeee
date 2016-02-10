#include "SnakeController.h"


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
