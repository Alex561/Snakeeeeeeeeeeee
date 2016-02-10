#ifndef POSITION_H
#define POSITION_H


struct Position
{
	int r;
	int c;

	bool operator==(const Position& other)
	{
		return this->r == other.r && this->c == other.c;
	}
};

#endif //POSITION_H
