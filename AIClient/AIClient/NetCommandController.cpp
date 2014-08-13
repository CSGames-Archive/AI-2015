#include "NetCommandController.h"

NetCommandController::NetCommandController(GameMap* gameMap)
{
	this->gameMap = gameMap;
	mState = Command::Init;
	mType = Command::None;
	x = 0;
	z = 0;
	playerId = 0;
	characterId = 0;
}

void NetCommandController::UpdateStateMachine(char* token)
{
	bool bIsDigit = true;

	switch(mState)
	{
	case Command::Init:
		if(!strcmp(token, "join"))
		{
			mType = Command::Join;
			mState = Command::WaitingPosX;
		}
		else if(!strcmp(token, "move"))
		{
			mType = Command::Move;
			mState = Command::WaitingPosX;
		}
		else if(!strcmp(token, "exit"))
		{
			mType = Command::Exit;
			mState = Command::ExitFunc;
		}
		break;

	case Command::WaitingPosX:
		for (int i = (int) strlen(token)-1; i > 0; i--)
			if (!isdigit(token[i]))
			{
				bIsDigit = false;
				break;
			}

		if(bIsDigit)
		{
			x = atoi(token);
			mState = Command::WaitingPosY;
		}
		else
		{
			mState = Command::Init;
		}
		break;

	case Command::WaitingPosY:
		for (int i = (int) strlen(token)-1; i > 0; i--)
			if (!isdigit(token[i]))
			{
				bIsDigit = false;
				break;
			}

		if(bIsDigit)
		{
			z = atoi(token);
			mState = Command::WaitingId;
		}
		else
		{
			mState = Command::Init;
		}
		break;

	case Command::WaitingId:
		for (int i = (int) strlen(token)-1; i > 0; i--)
			if (!isdigit(token[i]))
			{
				bIsDigit = false;
				break;
			}

		if(bIsDigit)
		{
			playerId = atoi(token);
			if(mType == Command::Join)
				PlayerJoin();
			else if (mType == Command::Move)
				PlayerMove();
		}

		mState = Command::Init;
		mType = Command::None;
		break;

	case Command::ExitFunc:
		mState = Command::Init;
		mType = Command::None;

		PlayerExit();
		break;
	}
}

void NetCommandController::PlayerJoin()
{
	std::cout << "Player " << playerId << " joined at X:" << x << ",Y:" << z << std::endl;

	gameMap->addPlayer(playerId, "NoName", NULL);
}

void NetCommandController::PlayerMove()
{
	std::cout << "Player " << playerId << " moved at X:" << x << ",Y:" << z << std::endl;

	gameMap->moveCharacter(playerId, characterId, x, z);
}

void NetCommandController::PlayerExit()
{
	std::cout << "Player " << playerId << " disconnected from the game" << std::endl;

	gameMap->quitPlayer(playerId);
}