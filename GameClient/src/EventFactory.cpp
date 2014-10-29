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

#include "stdafx.h"

#include "EventFactory.h"


EventController* eventController;
GameEvent* currentEvent;

char* arguments[MESSAGE_MAX_ARGUMENT];
int argumentCount;
void send();

EventFactory::EventFactory(EventController* eventController)
{
	this->eventController = eventController;
	argumentCount = 0;
}

EventFactory::~EventFactory()
{
}

void EventFactory::fead(char* token)
{
	if(!currentEvent)
	{
		createEvent(token);
	}
	else
	{
		arguments[argumentCount++] = token;
		
		if(argumentCount == currentEvent->getNumberOfArgument())
		{
			sendEvent();
		}
	}
}

void EventFactory::createEvent(char* token)
{
	if(!strcmp(token, "Error"))
	{
		currentEvent = new ErrorEvent();
	}
	else if(!strcmp(token, "Disconnect"))
	{
		currentEvent = new DisconnectEvent();
	}
	else if(!strcmp(token, "AddPlayer"))
	{
		currentEvent = new AddPlayerEvent();
	}
	else if(!strcmp(token, "Move"))
	{
		currentEvent = new MoveCharacterEvent();
	}
}

void EventFactory::sendEvent()
{
	currentEvent->fillArgument(arguments);
	eventController->addGameEvent(currentEvent);
	currentEvent = NULL;
	argumentCount = 0;
}
