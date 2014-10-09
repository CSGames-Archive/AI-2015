/* ---------------------------------------------------------------------------
**      _____      _____      _____   
**     /     \    /  _  \    /  _  \  
**    /  \ /  \  /  /_\  \  /  /_\  \ 
**   /    Y    \/    |    \/    |    \
**   \____|__  /\____|__  /\____|__  /
**           \/         \/         \/ 
**
** NetworkController.h
** Controller that manage all the network information
**
** Author: Moba Action Alpha Team
** -------------------------------------------------------------------------*/

#ifndef __NetworkController_h_
#define __NetworkController_h_

#include "stdafx.h"

#include <queue>
#include <iostream>

#include "NetCommandController.h"
#include "NetPlayerController.h"

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
	NetPlayerController* netPlayerController;

public:
    NetworkController(NetPlayerController* netPlayerController);
    virtual ~NetworkController();
	void readerFunc();
	void writeFunc();
	void init();
	void reset();
	void addMessageToQueue(std::string message);
	void waitTerminate();

	// Character specifics commandes
	void updatePosition(int x, int y);
	void close();
};

#endif // #ifndef __NetworkController_h_