#include "SnakeGame.h"
#include <iostream>
#include <iomanip>

#include "SnakeController.h"

//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

SnakeGame::SnakeGame()
	: snake1_(this, Direction::RIGHT, 1),
	snake2_(this, Direction::UP, 2)
{
	reset();
}


SnakeGame::~SnakeGame()
{
}

void SnakeGame::reset()
{
	running_ = true;
	snake1_ = Snake(this, Direction::RIGHT, 1);
	snake2_ = Snake(this, Direction::UP, 2);
	p1Score_ = 0;
	p2Score_ = 0;

	food_.reset(gameBoard_.getRandomPosition());


	snake1_.getSegments().push_back(Position{ 5, 7 });
	snake1_.getSegments().push_back(Position{ 5, 6 });
	snake1_.getSegments().push_back(Position{ 5, 5 });

	snake2_.getSegments().push_back(Position{ 15, 7 });
	snake2_.getSegments().push_back(Position{ 16, 7 });
	snake2_.getSegments().push_back(Position{ 17, 7 });
}

bool SnakeGame::isOver()
{
	return !running_;
}

Snake& SnakeGame::getSnake1()
{
	return snake1_;
}

Snake& SnakeGame::getSnake2()
{
	return snake2_;
}

bool SnakeGame::isValid(const Position& pos)
{
	return !(pos.r < 0 || pos.r >= gameBoard_.ROWS ||
		pos.c < 0 || pos.c >= gameBoard_.COLS);
}

bool SnakeGame::isFood(const Position& pos)
{
	return food_.getPosition() == pos;
}

bool SnakeGame::isSegment(const Position& pos)
{
	for (Position& p : snake1_.getSegments())
	{
		if (p == pos)
		{
			return true;
		}
	}

	for (Position& p : snake2_.getSegments())
	{
		if (p == pos)
		{
			return true;
		}
	}
	return false;
}

Food& SnakeGame::getFood()
{
	return food_;
}

void SnakeGame::run()
{
	draw();
	while(running_)
	{
		processInput();
		update();
		draw();
	}	
	std::cin.ignore();
}

void SnakeGame::endGame(const std::string& message)
{
	std::cout << message << std::endl;
	running_ = false;
}

void SnakeGame::processInput()
{
	/*std::string  s;
	std::cin >> s;
	
	SnakeController::control(snake1_, s);

	std::cin >> s;

	SnakeController::control(snake2_, s);*/

	std::cin.ignore();
}

void SnakeGame::update()
{
	gameBoard_.clear();
	snake1_.move();
	snake2_.move();
	if (food_.eaten())
	{
		food_.reset(gameBoard_.getRandomPosition());
	}

	for (Position& p : snake1_.getSegments())
	{
		gameBoard_.set(p, SNAKE1);
	}
	for (Position& p : snake2_.getSegments())
	{
		gameBoard_.set(p, SNAKE2);
	}
	gameBoard_.set(food_.getPosition(), FOOD);
}

void SnakeGame::draw()
{
	std::cout << "===== BOARD =====" << std::endl;
	std::cout << std::setw(3) << "";
	for (int c = 0; c < GameBoard::COLS; ++c)
	{
		std::cout << std::setw(3) << c ;
	}
	std::cout << std::endl;

	for (int r = 0; r < GameBoard::ROWS; ++r)
	{
		std::cout <<  std::setw(3) << r;
		for (int c = 0; c < GameBoard::COLS; ++c)
		{
			std::cout << std::setw(3) << gameBoard_.get(Position{ r, c });
		}
		std::cout << std::endl;
	}
}
