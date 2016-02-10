#ifndef FOOD_H
#define FOOD_H

#include "Position.h"
//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

class Food
{
public:
	Food();
	~Food();

	void reset(const Position& newPosition);

	void setPosition(const Position& newPosition);
	Position getPosition();

	bool eaten();
	void eat();

private:
	bool eaten_;
	Position pos_;
};

#endif //FOOD_H