#ifndef __NetCommandController__
#define __NetCommandController__

#include <iostream>
#include "NetPlayerController.h"

namespace Command
{
	enum State { Init, WaitingPosX, WaitingPosY, WaitingId, ExitFunc };
	enum CommandType { None, Join, Move, Exit };
};

class NetCommandController
{
private:
	NetPlayerController* netPlayerController;
	Command::State mState;
	Command::CommandType mType;
	double x;
	double z;
	int playerId;
	int characterId;

public:
	NetCommandController(NetPlayerController* netPlayerController);
	void UpdateStateMachine(char* token);
	void PlayerJoin();
	void PlayerMove();
	void PlayerExit();
};

#endif
