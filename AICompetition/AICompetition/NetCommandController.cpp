#include "NetCommandController.h"

NetCommandController::NetCommandController(NetPlayerController* netPlayerController)
{
	this->netPlayerController = netPlayerController;
	mState = Command::Init;
	mType = Command::None;
	position.x = 0;
	position.y = 0;
	position.z = 0;
	id = 0;
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
		for (int i = strlen(token)-1; i > 0; i--)
			if (!isdigit(token[i]))
			{
				bIsDigit = false;
				break;
			}

		if(bIsDigit)
		{
			position.x = atoi(token);
			mState = Command::WaitingPosY;
		}
		else
		{
			mState = Command::Init;
		}
		break;

	case Command::WaitingPosY:
		for (int i = strlen(token)-1; i > 0; i--)
			if (!isdigit(token[i]))
			{
				bIsDigit = false;
				break;
			}

		if(bIsDigit)
		{
			position.z = atoi(token);
			mState = Command::WaitingId;
		}
		else
		{
			mState = Command::Init;
		}
		break;

	case Command::WaitingId:
		for (int i = strlen(token)-1; i > 0; i--)
			if (!isdigit(token[i]))
			{
				bIsDigit = false;
				break;
			}

		if(bIsDigit)
		{
			id = atoi(token);
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
	std::cout << "Player " << id << " joined at X:" << position.x << ",Y:" << position.z << std::endl;

	netPlayerController->joinPlayer(id, position);
}

void NetCommandController::PlayerMove()
{
	std::cout << "Player " << id << " moved at X:" << position.x << ",Y:" << position.z << std::endl;
	netPlayerController->movePlayer(id, position);
}

void NetCommandController::PlayerExit()
{
	std::cout << "Player " << id << " disconnected from the game" << std::endl;
	netPlayerController->quitPlayer(id);
}