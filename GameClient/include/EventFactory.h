/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetCommandController.h
** The controler for all the command receive over the network
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __EventFactory__
#define __EventFactory__

#include "stdafx.h"

#include "GameEvent.h"

class EventFactory
{
private:
	std::queue<GameEvent*>* gameEventQueue;
	GameEvent* currentEvent;

	std::string arguments[MESSAGE_MAX_ARGUMENT];
	int argumentCount;
	void sendEvent();
	void createEvent(char* token);

public:
	EventFactory(std::queue<GameEvent*>* gameEventQueue);
    virtual ~EventFactory();

	void fead(char* token);
};

#endif // #ifndef __EventFactory__
