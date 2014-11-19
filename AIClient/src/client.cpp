/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Main.cpp
** The main function to test the ai client
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include <iostream>

#include "NetworkController.h"
#include "GameMap.h"

namespace
{
	enum AiStatus {AddPlayer, WaitGameStart, MoveToCorner, WaitReachCorner};
};

int main(int argc, char* argv[])
{
	try
	{
		char* playerName = "Rudolf";
		char* characterName1 = "dodo";
		char* characterName2 = "potato";
		char* characterNames[2] = {characterName1, characterName2};

		GameMap gameMap(playerName, characterNames);
		AiStatus myStatus = AiStatus::AddPlayer;
		NetworkController netController(&gameMap);

		netController.init();

		bool exit = false;

		std::string message = "";

		while(!exit)
		{
			if(netController.isConnected())
			{
				if(myStatus == AiStatus::AddPlayer)
				{
					boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
					char numstr[21]; // enough to hold all numbers up to 64-bits
					sprintf_s(numstr, "%d", gameMap.yourId);
					std::string message = "AddPlayer:";
					message += playerName;
					message += numstr;
					message += ":";
					message += characterName1;
					message += numstr;
					message += ":";
					message += characterName2;
					message += numstr;
					netController.addMessageToQueue(message);
					myStatus = AiStatus::WaitGameStart;
				}
				else if(myStatus == AiStatus::WaitGameStart && netController.isGameStarted())
				{
					myStatus = AiStatus::MoveToCorner;
				}
				else if(myStatus == AiStatus::MoveToCorner)
				{
					char numstr[21]; // enough to hold all numbers up to 64-bits
					sprintf_s(numstr, "%d", 50);
					std::string message = "Move:";
					message += numstr;
					message += ":";
					message += numstr;
					message += ":";
					sprintf_s(numstr, "%d", 1);
					message += numstr;
					netController.addMessageToQueue(message);
					myStatus = AiStatus::WaitReachCorner;
				}
			}
		}

		netController.close();
	}
	catch (std::exception& e)
	{
		printf("Exception in main : %s\n", e.what());
	}
}