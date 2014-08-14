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

#include "NetPlayerController.h"

NetPlayerController::NetPlayerController(std::queue<std::string>* messageQueue)
{
	this->messageQueue = messageQueue;
}

NetPlayerController::~NetPlayerController()
{

}

void NetPlayerController::addPlayer(int id, char* playerName, char* characterNames[maxCharacter])
{
	netPlayers[id] = new NetPlayer(messageQueue, playerName, id, characterNames);

	messageQueue->push(NetUtility::updatePlayer(id));
	
	for( int i=0; i<maxCharacter; ++i)
	{
		// TODO: use the map to check the starting position
		netPlayers[id]->moveCharacter(i, i*100, i*100);
	}
}

void NetPlayerController::quitPlayer(int id)
{
	std::map<int, NetPlayer*>::iterator it = netPlayers.find(id);
	NetPlayer* disconnectedPlayer = it->second;
	netPlayers.erase(it);
	delete disconnectedPlayer;
}

void NetPlayerController::moveCharacter(int playerId, int characterId, double x, double y)
{
	NetPlayer* targetPlayer = netPlayers.find(playerId)->second;
	if(targetPlayer)
	{
		targetPlayer->moveCharacter(characterId, x, y);
	}
}