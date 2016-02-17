#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <string>

#include "GameBoard.h"
#include "Snake.h"
#include "Food.h"

#include "websocket.h"

//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

class SnakeGame
{
public:
	static const char EMPTY = '.';
	static const char SNAKE1 = '1';
	static const char SNAKE2 = '2';
	static const char FOOD = 'O';

public:
	int p1Score_;
	int p2Score_;
	SnakeGame();
	~SnakeGame();

	void reset();

	bool isOver();

	Snake& getSnake1();
	Snake& getSnake2();

	bool isValid(const Position& pos);
	bool isFood(const Position& pos);
	bool isSegment(const Position& pos);

	Food& getFood();

	void update();

	void run();
	void endGame(const std::string& message);


private:
	bool running_;
	GameBoard gameBoard_;
	Food food_;
	Snake snake1_;
	Snake snake2_;

private:
	void processInput();
	void draw();
};

#endif //SNAKE_GAME_H