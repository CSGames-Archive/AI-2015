/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetworkController.h
** Controller that manage all the network information
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __NetworkController_h_
#define __NetworkController_h_

#include "stdafx.h"

#include "EventFactory.h"
#include "NetUtility.h"

using boost::asio::ip::tcp;

namespace
{
	enum ControllerStatus { TryToConnect, TryJoinGame, WaitingYouAreTheGameClient, Connected};
};

class NetworkController
{
private:
	// Structure
	std::queue<std::string> messageQueue;
	EventFactory eventFactory;

	// Attributes for connection
	boost::asio::io_service io_service;
	tcp::resolver resolver;
	tcp::resolver::query query;
	tcp::resolver::iterator endpoint_iterator;
	tcp::socket socket;
	ControllerStatus status;

	// Attributes for reader
	boost::thread* readerThread;
	boost::array<char, 128> buf;
	boost::system::error_code error;

	// Attributes for writer
	boost::thread* writerThread;

public:
    NetworkController(std::queue<GameEvent*>* gameEventQueue);
    virtual ~NetworkController();

	// Threads functions
	void readerFunc();
	void writeFunc();
	void init();
	bool tryToConnect();
	void tryJoinGame();
	void parseMessage(char* token);

	void close();
	std::queue<std::string>* getQueue();
};

#endif // #ifndef __NetworkController_h_