#include "GameBoard.h"

#include "SnakeGame.h"

#include "RNG.h"

//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

GameBoard::GameBoard()
	:board_(ROWS, std::vector<char>(COLS, SnakeGame::EMPTY))
{
}


GameBoard::~GameBoard()
{
}

void GameBoard::clear()
{
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			set(Position{ r, c }, SnakeGame::EMPTY);
		}
	}
}

void GameBoard::set(const Position& position, char value)
{
	board_.at(position.r).at(position.c) = value;
}

char GameBoard::get(const Position& position)
{
	return board_.at(position.r).at(position.c);
}

Position GameBoard::getRandomPosition()
{
	int randRow = RNG::getInt(0, ROWS);
	int randCol = RNG::getInt(0, COLS);
	return Position{ randRow, randCol };
}
