#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>

#include "Position.h"

class GameBoard
{
public:
	static const int ROWS = 20;
	static const int COLS = 20;

public:
	GameBoard();
	~GameBoard();

	void clear();

	void set(const Position& position, char value);
	char get(const Position& position);

	Position getRandomPosition();

private:
	std::vector<std::vector<char>> board_;
};


#endif //GAME_BOARD_H