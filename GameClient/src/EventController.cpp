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

void EventController::executeAllGameEvent()
{
	while(!QueueController::getInstance().isGameEventQueueEmpty())
	{
		GameEvent* gameEvent = QueueController::getInstance().getEvent();
		dispatchEvent(gameEvent);
		delete gameEvent;
	}
}

void EventController::dispatchEvent(GameEvent* gameEvent)
{
	if(gameEvent->getType() == EventType::ERROR_MESSAGE)
	{
		error(gameEvent);
	}
	else if(gameEvent->getType() == EventType::DISCONNECT)
	{
		disconnect(gameEvent);
	}
	else if(gameEvent->getType() == EventType::ADD_TEAM)
	{
		addTeam(gameEvent);
	}
	else if(gameEvent->getType() == EventType::MOVE_CHARACTER)
	{
		moveCharacter(gameEvent);
	}
	else if(gameEvent->getType() == EventType::DROP_MINE)
	{
		dropMine(gameEvent);
	}
	else if(gameEvent->getType() == EventType::MINE_HIT)
	{
		mineHit(gameEvent);
	}
	else if(gameEvent->getType() == EventType::THROW_MISSILE)
	{
		throwMissile(gameEvent);
	}
	else if(gameEvent->getType() == EventType::MISSILE_HIT)
	{
		missileHit(gameEvent);
	}
}

void EventController::error(GameEvent* gameEvent)
{
	ErrorEvent* errorEvent = static_cast<ErrorEvent*>(gameEvent);
	std::cout << "Error :" << errorEvent->message << std::endl;
}

void EventController::disconnect(GameEvent* gameEvent)
{
	DisconnectEvent* disconnectEvent = static_cast<DisconnectEvent*>(gameEvent);
	std::cout << "Player " << disconnectEvent->teamId << " disconnected from the game" << std::endl;

	World::getInstance().removeTeam(disconnectEvent->teamId);
}

void EventController::addTeam(GameEvent* gameEvent)
{
	AddTeamEvent* addTeamEvent = static_cast<AddTeamEvent*>(gameEvent);
	std::cout << "Team " << addTeamEvent->teamId << " join with name " << addTeamEvent->teamName << std::endl;
	for( int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		std::cout << "    * Character " << addTeamEvent->characterNames[i] << " enter the battlefield" << std::endl;
	}

	World::getInstance().addTeam(addTeamEvent->teamId, addTeamEvent->teamName, addTeamEvent->characterNames);
}

void EventController::moveCharacter(GameEvent* gameEvent)
{
	MoveCharacterEvent* moveEvent = static_cast<MoveCharacterEvent*>(gameEvent);
	std::cout << "Team " << moveEvent->teamId << " move character " << moveEvent->characterId << 
				 " to (" << moveEvent->positionX << "," << moveEvent->positionZ << ")" << std::endl;

	World::getInstance().getTeam(moveEvent->teamId)->getCharacter(moveEvent->characterId)->setTargetPosition(moveEvent->positionX, moveEvent->positionZ);
}

void EventController::dropMine(GameEvent* gameEvent)
{
	DropMineEvent* dropMineEvent = static_cast<DropMineEvent*>(gameEvent);
	std::cout << "Team " << dropMineEvent->teamId << " character " << dropMineEvent->characterId << " drop a mine" << std::endl;

	World::getInstance().getTeam(dropMineEvent->teamId)->getCharacter(dropMineEvent->characterId)->askMine();
}

void EventController::mineHit(GameEvent* gameEvent)
{
	MineHitEvent* dropMineEvent = static_cast<MineHitEvent*>(gameEvent);
	World::getInstance().mineHit(dropMineEvent->hitTeamId, dropMineEvent->hitCharacterId, dropMineEvent->originTeamId, dropMineEvent->originCharacterId);
}

void EventController::throwMissile(GameEvent* gameEvent)
{
	ThrowMissileEvent* throwMissileEvent = static_cast<ThrowMissileEvent*>(gameEvent);
	std::cout << "Team " << throwMissileEvent->teamId << " character " << throwMissileEvent->characterId << " throw a missile" << std::endl;

	World::getInstance().getTeam(throwMissileEvent->teamId)->getCharacter(throwMissileEvent->characterId)->askMissile(throwMissileEvent->direction);
}

void EventController::missileHit(GameEvent* gameEvent)
{
	MissileHitEvent* missileHitEvent = static_cast<MissileHitEvent*>(gameEvent);
	World::getInstance().missileHit(missileHitEvent->hitTeamId, missileHitEvent->hitCharacterId, missileHitEvent->originTeamId, missileHitEvent->originCharacterId);
}