/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** GameEvent.h
** All the event that can happen in a game
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __GameEvent_h_
#define __GameEvent_h_

#include "stdafx.h"

#include "World.h"
#include "NetUtility.h"

class GameEvent
{
protected:
	int convertCharToNumeral(std::string token);

public:
	GameEvent() {}
	virtual ~GameEvent() {}

	virtual void execute(World* world) {}
	virtual bool fill(std::string arguments) {return true;}
};

class ErrorEvent : public GameEvent
{
private:
	std::string message;

public:
	ErrorEvent() {}
	virtual ~ErrorEvent() {}

	virtual void execute(World* world);
	virtual bool fill(std::string arguments);
};

class DisconnectEvent : public GameEvent
{
private:
	int teamId;

public:
	DisconnectEvent() {}
	virtual ~DisconnectEvent() {}

	virtual void execute(World* world);
	virtual bool fill(std::string arguments);
};

class AddTeamEvent : public GameEvent
{
private:
	int teamId;
	std::string teamName;
	std::string characterNames[MAX_CHARACTER_PER_TEAM];

public:
	AddTeamEvent() {}
	virtual ~AddTeamEvent() {}

	virtual void execute(World* world);
	virtual bool fill(std::string arguments);
};

class MoveCharacterEvent : public GameEvent
{
private:
	int positionX, positionZ, characterId, teamId;
public:
	MoveCharacterEvent() {}
	virtual ~MoveCharacterEvent() {}

	virtual void execute(World* world);
	virtual bool fill(std::string arguments);
};

#endif // #ifndef __GameEvent_h_