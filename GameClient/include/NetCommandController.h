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
	Vector3 position;
	int id;

public:
	NetCommandController(NetPlayerController* netPlayerController);
	void UpdateStateMachine(char* token);
	void PlayerJoin();
	void PlayerMove();
	void PlayerExit();
};

#endif
