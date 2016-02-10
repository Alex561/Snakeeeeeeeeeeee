#ifndef FOOD_H
#define FOOD_H

#include "Position.h"

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