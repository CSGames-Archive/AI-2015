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

class GameEvent
{
protected:
	int convertCharToNumeral(char* token);

public:
	GameEvent() {}
	virtual ~GameEvent() {}

	virtual void execute(World* world) {}
	virtual bool fillArgument(char* values[]) {return true;}
	virtual int getNumberOfArgument() {return 0;}
};

class ErrorEvent : public GameEvent
{
private:
	char* message;

public:
	ErrorEvent() {}
	virtual ~ErrorEvent() {}

	virtual void execute(World* world);
	virtual bool fillArgument(char* values[]);
	virtual int getNumberOfArgument() {return 1;}
};

class DisconnectEvent : public GameEvent
{
private:
	int teamId;

public:
	DisconnectEvent() {}
	virtual ~DisconnectEvent() {}

	virtual void execute(World* world);
	virtual bool fillArgument(char* values[]);
	virtual int getNumberOfArgument() {return 1;}
};

class AddTeamEvent : public GameEvent
{
private:
	int teamId;
	char* teamName;
	char* characterNames[MAX_CHARACTER_PER_TEAM];

public:
	AddTeamEvent() {}
	virtual ~AddTeamEvent() {}

	virtual void execute(World* world);
	virtual bool fillArgument(char* values[]);
	virtual int getNumberOfArgument();
};

class MoveCharacterEvent : public GameEvent
{
private:
	int positionX, positionZ, characterId, teamId;
public:
	MoveCharacterEvent() {}
	virtual ~MoveCharacterEvent() {}

	virtual void execute(World* world);
	virtual bool fillArgument(char* values[]);
	virtual int getNumberOfArgument() {return 4;}
};

#endif // #ifndef __GameEvent_h_