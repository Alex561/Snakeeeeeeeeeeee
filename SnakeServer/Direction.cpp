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