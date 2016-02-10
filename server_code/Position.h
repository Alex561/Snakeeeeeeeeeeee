#ifndef POSITION_H
#define POSITION_H

//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

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
