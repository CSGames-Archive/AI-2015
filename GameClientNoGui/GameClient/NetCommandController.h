#ifndef __NetCommandController__
#define __NetCommandController__

#include <iostream>
#include "NetPlayerController.h"

namespace Command
{
	enum State { Init, WaitingDescription, WaitingPlayerId, WaitingPlayerName, WaitingCharacterName,
				 WaitingPosX, WaitingPosZ, WaitingCharacterId };
	enum CommandType { None, Error, Disconnect, AddPlayer, Move };
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
	char* description;
	char* playerName;

	int characterCount;
	char* characterNames[maxCharacter];

public:
	NetCommandController(NetPlayerController* netPlayerController);
	void UpdateStateMachine(char* token);
	
	void Error();
	void Disconnect();
	void AddPlayer();
	void MoveCharacter();
	void OkForExit();
};

#endif
