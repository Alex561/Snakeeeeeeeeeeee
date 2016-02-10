#include "Snake.h"

#include <iostream>

#include "SnakeGame.h"

Snake::Snake(SnakeGame& game, Direction dir)
	: game_(game),
	dir_(dir)
{
}


Snake::~Snake()
{
}

void Snake::move()
{
	int deltaR = 0;
	int deltaC = 0;
	switch (dir_)
	{
	case Direction::UP:
		deltaR = -1;
		break;
	case Direction::DOWN:
		deltaR = 1;
		break;
	case Direction::LEFT:
		deltaC = -1;
		break;
	case Direction::RIGHT:
		deltaC = 1;
		break;
	}
	
	Position newPos = Position{ segments_[0].r + deltaR, segments_[0].c + deltaC };

	if (!game_.isValid(newPos))
	{
		game_.endGame("This snake ran off screen");
	}
	else if (game_.isFood(newPos))
	{
		segments_.insert(segments_.begin(), newPos);
		game_.getFood().eat();
	}
	else if (game_.isSegment(newPos))
	{
		game_.endGame("This snake ran into a segment and died");
	}
	else //normal movement
	{
		segments_.insert(segments_.begin(), newPos);
		segments_.pop_back();
	}

}

void Snake::changeDirection(Direction newDir)
{
	//don't let snake turn backwards
	if (!oppositeDir(dir_, newDir))
	{
		dir_ = newDir;
	}
}

std::vector<Position>& Snake::getSegments()
{
	return segments_;
}

bool Snake::oppositeDir(Direction a, Direction b)
{
	switch (a)
	{
	case Direction::UP:
		return b == Direction::DOWN;
	case Direction::DOWN:
		return b == Direction::UP;
	case Direction::LEFT:
		return b == Direction::RIGHT;
	case Direction::RIGHT:
		return b == Direction::LEFT;
	default:
		std::cout << "This shouldn't print" << std::endl;
		return false;
	}
}
