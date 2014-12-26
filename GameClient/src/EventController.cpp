/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**         \/        \/             \/         \/         \/        \/        \/ 
**
** EventController.h
** The controler for all the event on the game
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "EventController.h"

EventController::EventController()
{
}

EventController::~EventController()
{
}

void EventController::executeAllGameEvent(World* world)
{
	while(!gameEventQueue.empty())
	{
		GameEvent* event = gameEventQueue.front();
		event->execute(world);
		//TODO: test if need delete event;
		gameEventQueue.pop();
		event;
	}
}

void EventController::addGameEvent(GameEvent* gameEvent)
{
	gameEventQueue.push(gameEvent);
}

std::queue<GameEvent*>* EventController::getQueue()
{
	return &gameEventQueue;
}
