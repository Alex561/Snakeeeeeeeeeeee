#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>

#include "Position.h"

//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

class GameBoard
{
public:
	static const int ROWS = 45;
	static const int COLS = 45;

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