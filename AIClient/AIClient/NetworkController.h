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

#include <queue>
#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "NetCommandController.h"
#include "GameMap.h"

using boost::asio::ip::tcp;

class NetworkController
{
private:
	// Attributes for connection
	boost::asio::io_service io_service;
	tcp::resolver resolver;
	tcp::resolver::query query;
	tcp::resolver::iterator endpoint_iterator;
	tcp::socket socket;

	// Attributes for reader
	boost::thread* readerThread;
	boost::array<char, 128> buf;
	boost::system::error_code error;
	NetCommandController netCommandController;

	// Attributes for writer
	std::queue<std::string> messageQueue;
	boost::thread* writerThread;

	// Attributes for the world
	GameMap* gameMap;

public:
    NetworkController(GameMap* gameMap);
    virtual ~NetworkController();

	// Threads functions
	void readerFunc();
	void writeFunc();
	void init();

	// Character specifics commandes
	void addMessageToQueue(std::string message);
	void updatePosition(int x, int y);
	void close();
};

#endif // #ifndef __NetworkController_h_