#ifndef SNAKE_CONTROLLER_H
#define SNAKE_CONTROLLER_H

#include "Snake.h"
#include <string>

//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

class SnakeController
{
public:
	static void control(Snake& snake, const std::string& input);
};

#endif //SNAKE_CONTROLLER_H