#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <string>

#include "GameBoard.h"
#include "Snake.h"
#include "Food.h"

#include "websocket.h"

class SnakeGame
{
public:
	static const char EMPTY = '.';
	static const char SNAKE1 = '1';
	static const char SNAKE2 = '2';
	static const char FOOD = 'O';

	static const int PORT_NUM = 44222;

	static webSocket SERVER;


public:
	SnakeGame();
	~SnakeGame();

	bool isValid(const Position& pos);
	bool isFood(const Position& pos);
	bool isSegment(const Position& pos);

	Food& getFood();


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
	void update();
	void draw();
};

#endif //SNAKE_GAME_H