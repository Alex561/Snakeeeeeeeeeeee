#include <iostream>
#include <sstream>

#include "SnakeGame.h"
#include <windows.h>
//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

const int PORT_NUM = 44222;
webSocket SERVER;
SnakeGame game;

bool p1_join = false;

int connection1 = -1;
int connection2 = -2;

std::string player1_ID = "";
std::string player2_ID = "";


std::vector<std::string> split(const std::string& input, char delimiter)
{
	std::istringstream ss(input);
	std::string token;
	std::vector<std::string> result;

	while (std::getline(ss, token, delimiter))
	{
		result.push_back(token);
	}
	return result;
}

void openHandler(int clientID)
{
	std::cout << "Connection from " << clientID << std::endl;
	SERVER.wsSend(clientID, "Connection received");
	/*if (connection != -1)
	{
	SnakeGame::SERVER.wsSend(clientID, "Game Rejected, only one allowed");
	SnakeGame::SERVER.wsClose(clientID);
	*/
	//connection = clientID;
}

void closeHandler(int clientID)
{
	std::cout << "Connection closed " << clientID << std::endl;
	SERVER.wsSend(clientID, "Connection closed");
	connection1 = -1;
	connection2 = -2;

}

void messageHandler(int clientID, string message)
{
	std::cout << "Message From " << clientID << ":" << message << std::endl;
	auto splitMessage = split(message, ';');

	std::string& firstToken = splitMessage[0];

	if (firstToken == "C_INIT")
	{
		if (!p1_join)
		{
			player1_ID = splitMessage[1];
			connection1 = clientID;
			p1_join = true;
		}
		else
		{
			player2_ID = splitMessage[1];
			connection2 = clientID;

			game.reset();

			SERVER.wsSend(connection1, "S_INIT;" + game.getSnake1().getHead().toString() + ";" + game.getSnake1().getTail().toString() + ";"
				+ game.getSnake2().getHead().toString() + ";" + game.getSnake2().getTail().toString() + ";" + game.getFood().getPosition().toString() + ';' + player2_ID);
			SERVER.wsSend(connection2, "S_INIT;" + game.getSnake2().getHead().toString() + ";" + game.getSnake2().getTail().toString() + ";"
				+ game.getSnake1().getHead().toString() + ";" + game.getSnake1().getTail().toString() + ";" + game.getFood().getPosition().toString() + ';' + player1_ID);
			
		}
	}
	else if (firstToken == "C_INPUT")
	{
		Direction d = fromString(splitMessage[1]);

		if (clientID == connection1)
		{
			game.getSnake1().changeDirection(d);
		}
		else if (clientID == connection2)
		{
			game.getSnake2().changeDirection(d);
		}
		else
		{
			std::cout << "this should never happppennnnn" << std::endl;
		}
	}
}


void periodicHandler()
{
	if (connection1 != -1 && connection2 != -2) {
		Sleep(500);
		if (!game.isOver())
		{
			game.update();
		}
		SERVER.wsSend(connection1, "S_UP;" + game.getSnake1().getHead().toString() + ";"
			+ game.getSnake2().getHead().toString() + ";" + game.getFood().getPosition().toString() + ";" + std::to_string(game.p1Score_) + ";" + std::to_string(game.p2Score_));
		SERVER.wsSend(connection2, "S_UP;" + game.getSnake2().getHead().toString() + ";"
			+ game.getSnake1().getHead().toString() + ";" + game.getFood().getPosition().toString() + ";" + std::to_string(game.p2Score_) + ";" + std::to_string(game.p1Score_));
		if (game.isOver())
		{
			SERVER.wsClose(connection1);
			SERVER.wsClose(connection2);
		}
	}
}

int main() 
{
	SERVER.setOpenHandler(openHandler);
	SERVER.setCloseHandler(closeHandler);
	SERVER.setMessageHandler(messageHandler);
	SERVER.setPeriodicHandler(periodicHandler);
	SERVER.startServer(PORT_NUM);

	return 0;
}