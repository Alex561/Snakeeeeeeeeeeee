#include "Direction.h"

#include <iostream>


Direction fromString(const std::string& str)
{
	if (str == "UP")
	{
		return Direction::UP;
	}
	else if (str == "DOWN")
	{
		return Direction::DOWN;
	}
	else if (str == "LEFT")
	{
		return Direction::LEFT;
	}
	else if (str == "RIGHT")
	{
		return Direction::RIGHT;
	}
	else
	{
		std::cout << "Error: Trying to convert " + str + " to direction" << std::endl;
		return Direction::UP;
	}
}

std::string toString(Direction d)
{
	switch (d)
	{
	case Direction::DOWN:
		return "DOWN";
	case Direction::UP:
		return "UP";
	case Direction::LEFT:
		return "LEFT";
	case Direction::RIGHT:
		return "RIGHT";
	default:
		std::cout << "Error converting to string" << std::endl;
		return "ERROR";
	}
}
