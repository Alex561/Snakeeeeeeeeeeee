#include "Food.h"



Food::Food()
{
}


Food::~Food()
{
}

void Food::reset(const Position& newPosition)
{
	setPosition(newPosition);
	eaten_ = false;
}

void Food::setPosition(const Position & newPosition)
{
	pos_ = newPosition;
}

Position Food::getPosition()
{
	return pos_;
}

bool Food::eaten()
{
	return eaten_;
}

void Food::eat()
{
	eaten_ = true;
}
