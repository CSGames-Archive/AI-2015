/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetPlayerController.cpp
** Implementation of the NetPlayerController
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "NetPlayerController.h"

NetPlayerController::NetPlayerController(SceneManager* sceneManager, std::queue<std::string>* messageQueue)
{
	this->messageQueue = messageQueue;
	this->sceneManager = sceneManager;
}

NetPlayerController::~NetPlayerController()
{

}

void NetPlayerController::addPlayer(int id, char* playerName, char* characterNames[maxCharacter])
{
	netTeams[id] = new NetTeam(sceneManager, messageQueue, playerName, id, characterNames);

	if(netTeams.size() == MAX_PLAYER)
	{
		typedef std::map<int, NetTeam*>::iterator it_type;
		for(it_type iterator = netTeams.begin(); iterator != netTeams.end(); ++iterator)
		{
			messageQueue->push(NetUtility::updatePlayer(iterator->first));

			for( int j=0; j<maxCharacter; ++j)
			{
				// TODO: use the map to check the starting position
				//Vector3 startingPosition();
				//iterat second->set(j, iterator->first*10, j*10);
			}
		}
	}
}

void NetPlayerController::quitPlayer(int id)
{
	std::map<int, NetTeam*>::iterator it = netTeams.find(id);
	NetTeam* disconnectedPlayer = it->second;
	netTeams.erase(it);
	delete disconnectedPlayer;
}

void NetPlayerController::setTargetPosition(int teamId, int characterId, double x, double y)
{
	Vector3 targetPosition(x, 0, y);
	NetTeam* targetTeam = netTeams.find(teamId)->second;
	if(targetTeam)
	{
		targetTeam->setTargetPosition(characterId, targetPosition);
	}
}

void NetPlayerController::addTime(Real deltaTime)
{
	typedef std::map<int, NetTeam*>::iterator it_type;
	for(it_type iterator = netTeams.begin(); iterator != netTeams.end(); ++iterator)
	{
		iterator->second->addTime(deltaTime);
	}
}