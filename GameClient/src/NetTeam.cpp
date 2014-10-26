/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetTeam.cpp
** Implementation of the NetTeam
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "NetTeam.h"

NetTeam::NetTeam(SceneManager* sceneManager, std::queue<std::string>* messageQueue, char* name, int teamId, char* characterNames[maxCharacter])
{
	this->name = "NoName";
	this->messageQueue = messageQueue;
	this->teamId = teamId;

	std::string meshName = "Tank.mesh";
	//TODO: update with the map
	Vector3 startingPosition = Vector3::ZERO;

	for(int i = 0; i < maxCharacter; ++i)
	{
		netCharacters[i] = new NetCharacter(sceneManager, messageQueue, characterNames[i], meshName, startingPosition, teamId, i);
	}
}

NetTeam::~NetTeam()
{
	for(int i = 0; i < maxCharacter; ++i)
	{
		if(netCharacters[i])
		{
			delete netCharacters[i];
		}
	}
}

void NetTeam::setTargetPosition(int characterId, Vector3 targetPosition)
{
	netCharacters[characterId]->setTargetPosition(targetPosition);
}

void NetTeam::addTime(Real deltaTime)
{
	for(int i = 0; i < maxCharacter; ++i)
	{
		netCharacters[i]->addTime(deltaTime);
	}
}