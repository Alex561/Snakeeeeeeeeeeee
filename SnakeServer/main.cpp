#include <iostream>
#include <sstream>

#include <queue>
#include <ctime>

#include "SnakeGame.h"
#include "RNG.h"
#include <windows.h>
#include <chrono>
//achapp 28191571 alex chapp
//andresg6 28662951 andres gonzalez
//klynaugh 25025195 kinsey lynaugh
//kgwong 93034206 kevin wong

using namespace std::chrono;

const int PORT_NUM = 44222;
webSocket SERVER;
SnakeGame game;

bool p1_join = false;

int connection1 = -1;
int connection2 = -2;

std::string player1_ID = "";
std::string player2_ID = "";

std::queue<string> p1_send_queue;
std::queue<string> p1_receive_queue;
int p1_send_latency = 0;
int p1_receive_latency = 0;
std::queue<string> p2_send_queue;
std::queue<string> p2_receive_queue;
int p2_send_latency = 0;
int p2_receive_latency = 0;

int countdown = 50;


void handleDequeuedMessage(int clientID, string message);

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

int getRandomLatency()
{
	int latency = RNG::getNormalInt(30, 10);
	return latency;
}

//adds to queue with delay
void serverSend(int clientID, string message)
{
	if (clientID == connection1)
	{
		p1_send_queue.push(message);
	}
	else if (clientID == connection2)
	{
		p2_send_queue.push(message);
	}
	else
	{
		std::cout << "You messed up in " << __FUNCTION__ << std::endl;
	}
}


//adds to receive queue
void serverReceive(int clientID, string message)
{
	if (clientID == connection1)
	{
		p1_receive_queue.push(message);
	}
	else if (clientID == connection2)
	{
		p2_receive_queue.push(message);
	}
	else
	{
		std::cout << "You messed up in " << __FUNCTION__ << std::endl;
	}
}

void sendQueuedMessages(int playerNum, std::queue<string>& queue, int& latencyValueRef)
{
	if (playerNum != 1 && playerNum != 2)
	{
		std::cout << "You messed up " << __FUNCTION__ << " " << playerNum << std::endl;
	}

	if (latencyValueRef <= 0 && !queue.empty())
	{
		int connection = playerNum == 1 ? connection1 : connection2;
		SERVER.wsSend(connection, queue.front());
		queue.pop();
		latencyValueRef = getRandomLatency();
	}
	else
	{
		--latencyValueRef;
	}
}

void receiveQueuedMessages(int playerNum, std::queue<string>& queue, int& latencyValueRef)
{
	//std::cout << latencyValueRef << std::endl;
	if (playerNum != 1 && playerNum != 2)
	{
		std::cout << "You messed up " << __FUNCTION__ << " " << playerNum << std::endl;
	}
	if (latencyValueRef <= 0 && !queue.empty())
	{
		int connection = playerNum == 1 ? connection1 : connection2;
		handleDequeuedMessage(connection, queue.front());
		queue.pop();
		latencyValueRef = getRandomLatency();
	}
	else if (latencyValueRef <= 0) {
		latencyValueRef = getRandomLatency();
	}
	else
	{
		--latencyValueRef;
	}
}

void handleDequeuedMessage(int clientID, string message)
{
	auto splitMessage = split(message, ';');
	std::string& firstToken = splitMessage[0];

	if (firstToken == "C_INIT")
	{
		if (clientID == connection1)
		{
			player1_ID = splitMessage[1];
		}
		else
		{
			player2_ID = splitMessage[1];
			game.reset();

			serverSend(connection1, "S_INIT;" + game.getSnake1().getHead().toString() + ";" + game.getSnake1().getTail().toString() + ";"
				+ game.getSnake2().getHead().toString() + ";" + game.getSnake2().getTail().toString() + ";" + game.getFood().getPosition().toString() + ';' + player2_ID + ';' + toString(game.getSnake1().getDirection()) + ';' + toString(game.getSnake2().getDirection()));
			serverSend(connection2, "S_INIT;" + game.getSnake2().getHead().toString() + ";" + game.getSnake2().getTail().toString() + ";"
				+ game.getSnake1().getHead().toString() + ";" + game.getSnake1().getTail().toString() + ";" + game.getFood().getPosition().toString() + ';' + player1_ID + ';' + toString(game.getSnake2().getDirection()) + ';' + toString(game.getSnake1().getDirection()));

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
	else if (firstToken == "C_TIMESTAMP")
	{
		std::string timeSent = splitMessage[1];

		std::chrono::milliseconds timeGot = duration_cast< milliseconds >(
			system_clock::now().time_since_epoch()
			);

		if (clientID == connection1)
		{
			std::chrono::milliseconds timeNow = duration_cast< milliseconds >(
				system_clock::now().time_since_epoch()
				); 
			serverSend(connection1, "S_TIMESTAMP;" + timeSent + ";" + std::to_string(timeGot.count()) + ";" + std::to_string(timeNow.count()));
		}
		else if (clientID == connection2)
		{
			std::chrono::milliseconds timeNow = duration_cast< milliseconds >(
				system_clock::now().time_since_epoch()
				);
			serverSend(connection2, "S_TIMESTAMP;" + timeSent + ";" + std::to_string(timeGot.count()) + ";" + std::to_string(timeNow.count()));
		}
		else
		{
			std::cout << "this should never happppennnnn" << std::endl;
		}
	}
}

void openHandler(int clientID)
{
	std::cout << "Connection from " << clientID << std::endl;
	SERVER.wsSend(clientID, "Connection received");
	if (!p1_join)
	{

		connection1 = clientID;
		p1_join = true;
	}
	else {
		connection2 = clientID;
	}

}

void closeHandler(int clientID)
{
	std::cout << "Connection closed " << clientID << std::endl;
	SERVER.wsSend(clientID, "Connection closed"); //for debugging, not for game
	connection1 = -1;
	connection2 = -2;

}

void messageHandler(int clientID, string message)
{
	std::cout << "Message From " << clientID << ":" << message << std::endl;
	serverReceive(clientID, message);
}


void periodicHandler()
{
	if (connection1 != -1 && connection2 != -2) {
		receiveQueuedMessages(1, p1_receive_queue, p1_receive_latency);
		receiveQueuedMessages(2, p2_receive_queue, p2_receive_latency);

		sendQueuedMessages(1, p1_send_queue, p1_send_latency);
		sendQueuedMessages(2, p2_send_queue, p2_send_latency);
		if (countdown == 0) {

			if (!game.isOver())
			{
				game.update();
			}
			serverSend(connection1, "S_UP;" + game.getSnake1().getHead().toString() + ";"
				+ game.getSnake2().getHead().toString() + ";" + game.getFood().getPosition().toString() + ";" + std::to_string(game.p1Score_) + ";" + std::to_string(game.p2Score_) + ';' + toString(game.getSnake2().getDirection()));
			serverSend(connection2, "S_UP;" + game.getSnake2().getHead().toString() + ";"
				+ game.getSnake1().getHead().toString() + ";" + game.getFood().getPosition().toString() + ";" + std::to_string(game.p2Score_) + ";" + std::to_string(game.p1Score_) + ';' + toString(game.getSnake1().getDirection()));




			if (game.isOver())
			{
				SERVER.wsClose(connection1);
				SERVER.wsClose(connection2);
			}
			countdown = 50;
		}
		else
		{
			countdown--;
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