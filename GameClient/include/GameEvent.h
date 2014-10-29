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
public:
    GameEvent();
    virtual ~GameEvent();

	virtual void execute(World* world) {}
	virtual bool fillArgument(char* values[]) {}
	virtual int getNumberOfArgument() {}
};

class ErrorEvent : public GameEvent
{
public:
    ErrorEvent();
    virtual ~ErrorEvent();

	virtual void execute(World* world) {}
	virtual bool fillArgument(char* values[]) {}
	virtual int getNumberOfArgument() {return 1;}
};

class DisconnectEvent : public GameEvent
{
public:
    DisconnectEvent();
    virtual ~DisconnectEvent();

	virtual void execute(World* world) {}
	virtual bool fillArgument(char* values[]) {}
	virtual int getNumberOfArgument() {return 1;}
};

class AddPlayerEvent : public GameEvent
{
public:
    AddPlayerEvent();
    virtual ~AddPlayerEvent();

	virtual void execute(World* world);
	virtual bool fillArgument(char* values[]);
	virtual int getNumberOfArgument();
};

class MoveCharacterEvent : public GameEvent
{
public:
    MoveCharacterEvent();
    virtual ~MoveCharacterEvent();

	virtual void execute(World* world);
	virtual bool fillArgument(char* values[]);
	virtual int getNumberOfArgument() {return 4;}
};

#endif // #ifndef __GameEvent_h_