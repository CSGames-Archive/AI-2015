/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**         \/        \/             \/         \/         \/        \/        \/ 
**
** EventController.h
** Controller that manage all the event
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __EventController_h_
#define __EventController_h_

#include "stdafx.h"

#include "GameEvent.h"

class EventController
{
private:
	std::queue<GameEvent*> gameEventQueue;

public:
    EventController();
    virtual ~EventController();

	void executeAllGameEvent(World* world);
	void addGameEvent(GameEvent* gameEvent);
	std::queue<GameEvent*>* getQueue();
};

#endif // #ifndef __EventController_h_