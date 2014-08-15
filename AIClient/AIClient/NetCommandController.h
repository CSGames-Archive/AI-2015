#ifndef __NetCommandController__
#define __NetCommandController__

#include <iostream>
#include "GameMap.h"

namespace Command
{
	enum State { Init, WaitingDescription, WaitingPlayerId, WaitingPosX, WaitingPosZ, 
				 WaitingCharacterId, WaitingGameClientId };
	enum CommandType { None, Error, YourId, UpdatePlayer, UpdateCharacter };
};

class NetCommandController
{
private:
	GameMap* gameMap;
	Command::State mState;
	Command::CommandType mType;
	double x;
	double z;
	int playerId;
	int characterId;
	char* description;

public:
	NetCommandController(GameMap* gameMap);
	void UpdateStateMachine(char* token);
	
	void Error();
	void YourId();
	void UpdatePlayer();
	void UpdateCharacter();
	void OkForExit();
};

#endif
