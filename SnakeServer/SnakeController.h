#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H

#include "Snake.h"
#include <string>

class SnakeController
{
public:
	static void control(Snake& snake, const std::string& input);
};

#endif //SNAKE_CONTROLLER_H