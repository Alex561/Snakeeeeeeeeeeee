#include "Food.h"


//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

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
