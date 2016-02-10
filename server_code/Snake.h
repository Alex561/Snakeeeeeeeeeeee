#ifndef SNAKE_H
#define SNAKE_H

#include "Direction.h"
#include "Position.h"

#include <vector>

//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

class SnakeGame;

class Snake
{
public:
	static const int START_LENGTH = 3;

public:
	Snake(SnakeGame& game, Direction dir);
	~Snake();

	void move();
	void changeDirection(Direction newDir);

	std::vector<Position>& getSegments();

private:
	SnakeGame& game_;
	Direction dir_; //current direction of movement

	//holds all the segments of the snake
	std::vector<Position> segments_;

private:
	//returns true of direction is opposite
	//so snake doesnt turn into itself
	bool oppositeDir(Direction a, Direction b);

};

#endif //SNAKE_H