/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** EventFactory.java
 ** Factory that generate event
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package event;

public class EventFactory {

}

/*

EventFactory::EventFactory(std::queue<GameEvent*>* gameEventQueue)
{
	this->gameEventQueue = gameEventQueue;
	argumentCount = 0;
	currentEvent = NULL;
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
		currentEvent = new AddTeamEvent();
	}
	else if(!strcmp(token, "Move"))
	{
		currentEvent = new MoveCharacterEvent();
	}
}

void EventFactory::sendEvent()
{
	if(currentEvent->fillArgument(arguments))
	{
		gameEventQueue->push(currentEvent);
	}
	currentEvent = NULL;
	argumentCount = 0;
}
*/