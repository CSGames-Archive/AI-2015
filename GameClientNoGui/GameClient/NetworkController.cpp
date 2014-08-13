/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetworkController.cpp
** Implementation of the NetworkController
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "NetworkController.h"

NetworkController::NetworkController(NetPlayerController* netPlayerController) : resolver(io_service), query("127.0.0.1", "1337"), socket(io_service), netCommandController(netPlayerController)
	{
		this->netPlayerController = netPlayerController;

		endpoint_iterator = resolver.resolve(query);
		readerThread = NULL;
		writerThread = NULL;
	}

NetworkController::~NetworkController()
{
	if(readerThread)
	{
		delete readerThread;
	}

	if(writerThread)
	{
		delete writerThread;
	}
}

void NetworkController::writeFunc()
{
	bool exit = false;
	try
	{
		std::string message = "";

		while(!exit)
		{
			if(!messageQueue.empty())
			{
				message = messageQueue.back();
				messageQueue.pop();

				if(message == "exit")
				{
					exit = true;
				}

				boost::system::error_code ignored_error;
				boost::asio::write(socket, boost::asio::buffer(message),
							   boost::asio::transfer_all(), ignored_error);
			}
		}
		readerThread->join();
		socket.close();
	}
	catch (std::exception& e)
	{
		printf("Exception in writter : %s\n", e.what());
	}
}

void NetworkController::init()
{
	try
	{
		boost::asio::connect(socket, endpoint_iterator);
		
		if(readerThread == NULL)
		{
			readerThread = new boost::thread( boost::bind (&NetworkController::readerFunc, this));
		}

		if(writerThread == NULL)
		{
			writerThread = new boost::thread( boost::bind (&NetworkController::writeFunc, this));
		}
	}
	catch (std::exception& e)
	{
		printf("Exception in init : %s\n", e.what());
	}
}

void  NetworkController::addMessageToQueue(std::string message)
{
	messageQueue.push(message);
}

void NetworkController::readerFunc()
{
	bool exit = false;
	try
	{
		while(!exit)
		{
			//we read the buffer to put the message in the buffer
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				throw boost::system::system_error(error); // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			buf.data()[len] = '\0';

			if(!std::strcmp(buf.data(), "ok"))
			{
				exit = true;
				break;
			}

			char* seps = ":";
			char* message = buf.data();
			char* token = NULL;
			char* next_token = NULL;

			token = strtok_s( message, seps, &next_token);

			while(token != NULL)
			{
				netCommandController.UpdateStateMachine(token);
				token = strtok_s( NULL, seps, &next_token);
			}
		}
	}
	catch (std::exception& e)
	{
		printf("Exception in reader : %s\n", e.what());
	}
}

void NetworkController::close()
{
	std::string message = "exit";
	addMessageToQueue(message);

	if(readerThread)
		readerThread->join();

	if(writerThread)
		writerThread->join();
}

// TODO: outdated function need the controle for multiple characters
void NetworkController::updatePosition(int x, int y)
{
	char numstr[21]; // enough to hold all numbers up to 64-bits
	sprintf(numstr, "%d", x);
	std::string message = "move:";
	message += numstr;
	message += ":";
	sprintf(numstr, "%d", y);
	message += numstr;
	addMessageToQueue(message);
}