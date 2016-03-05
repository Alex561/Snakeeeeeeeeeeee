#ifndef DIRECTION_H
#define DIRECTION_H

#include <string>

//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

enum class Direction 
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

Direction fromString(const std::string& str);
std::string toString(Direction d);

#endif //DIRECTION_H