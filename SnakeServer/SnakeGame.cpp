#include "SnakeGame.h"

#include <iostream>
#include <iomanip>

#include "SnakeController.h"

webSocket SnakeGame::SERVER;

void openHandler1234(int clientID)
{
	std::cout << "Connection from " << clientID << std::endl;
	SnakeGame::SERVER.wsSend(clientID, "Connection received");
}

void closeHandler1234(int clientID)
{
	std::cout << "Connection closed " << clientID << std::endl;
	SnakeGame::SERVER.wsSend(clientID, "Connection closed");
}

void messageHandler1234(int clientID, string message)
{
	std::cout << "Message From " << clientID << ":" << message << std::endl;
//	SnakeGame::SERVER.wsSend(clientID, "anything that tickles my bunyons");
}

SnakeGame::SnakeGame()
	:running_(true),
	snake1_(*this, Direction::RIGHT),
	snake2_(*this, Direction::UP)
{

	SERVER.setOpenHandler(openHandler1234);
	SERVER.setCloseHandler(closeHandler1234);
	SERVER.setMessageHandler(messageHandler1234);
	SERVER.startServer(PORT_NUM);

	food_.reset(gameBoard_.getRandomPosition());

	snake1_.getSegments().push_back(Position{5, 7});
	snake1_.getSegments().push_back(Position{5, 6});
	snake1_.getSegments().push_back(Position{5, 5});
	
	snake2_.getSegments().push_back(Position{15, 7});
	snake2_.getSegments().push_back(Position{16, 7});
	snake2_.getSegments().push_back(Position{17, 7});
}


SnakeGame::~SnakeGame()
{
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
		//sendGameState here instead of draw
		draw();
	}	
	std::cin.ignore();
}

void SnakeGame::endGame(const std::string& message)
{
	std::cout << message << std::endl;
	running_ = false;
	std::cin.ignore();
}

void SnakeGame::processInput()
{
	std::string  s;
	std::cin >> s;
	
	SnakeController::control(snake1_, s);

	std::cin >> s;

	SnakeController::control(snake2_, s);
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
