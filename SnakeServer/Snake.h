#ifndef SNAKE_H
#define SNAKE_H

#include "Direction.h"
#include "Position.h"

#include <vector>

class SnakeGame;

//MIGHT NEED A REFERENCE TO THE BOARD
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