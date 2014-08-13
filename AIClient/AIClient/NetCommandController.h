#ifndef __NetCommandController__
#define __NetCommandController__

#include <iostream>
#include "GameMap.h"

namespace Command
{
	enum State { Init, WaitingPosX, WaitingPosY, WaitingId, ExitFunc };
	enum CommandType { None, Join, Move, Exit };
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

public:
	NetCommandController(GameMap* gameMap);
	void UpdateStateMachine(char* token);
	void PlayerJoin();
	void PlayerMove();
	void PlayerExit();
};

#endif
