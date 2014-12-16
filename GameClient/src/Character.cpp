/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetCharacter.h
** Implementation of the NetCharacter
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "Character.h"

Character::Character(std::queue<std::string>* netMessageQueue, Ogre::SceneNode* bodyNode, std::string name, int teamId, int characterId)
{
	// Network
	this->netMessageQueue = netMessageQueue;
	this->teamId = teamId;
	this->characterId = characterId;

	// 3d Infos
	this->bodyNode = bodyNode;

	// Character Infos
	this->name = name;
	this->targetPosition = bodyNode->getPosition();
	this->lastSendPosition = bodyNode->getPosition();
}

Character::~Character()
{
}

void Character::addTime(Ogre::Real deltaTime)
{
	updateBody(deltaTime);
}

void Character::setTargetPosition(Ogre::Vector3 targetPosition)
{
	targetPosition.y = bodyNode->getPosition().y;
	this->targetPosition = targetPosition;
}

void Character::setTargetPosition(int x, int z)
{
	Ogre::Vector3 targetPosition(x, bodyNode->getPosition().y, z);
	this->targetPosition = targetPosition;
}

void Character::updateBody(Ogre::Real deltaTime)
{
	if(bodyNode != NULL)
	{
		Ogre::Vector3 currentPosition = bodyNode->getPosition();
		Ogre::Vector3 goalDirection = targetPosition - currentPosition;

		if(goalDirection.length() > Ogre::Real(1.0))
		{
			goalDirection.normalise();
		}
		else
		{
			goalDirection = Ogre::Vector3::ZERO;
		}

		if (goalDirection != Ogre::Vector3::ZERO)
		{
			// Calculate direction
			Ogre::Quaternion currentDirection = bodyNode->getOrientation().zAxis().getRotationTo(goalDirection);

			// Find the rotation in yaw
			Ogre::Real yawToGoal = currentDirection.getYaw().valueDegrees();

			bodyNode->yaw(Ogre::Degree(yawToGoal));

			bodyNode->translate(0, 0, deltaTime * WALK_SPEED, Ogre::Node::TS_LOCAL);
		}

		// TODO: refactor with case
		Ogre::Vector3 networkDivergence = lastSendPosition - currentPosition;
		if(networkDivergence.length() > 25)
		{
			std::string message = NetUtility::generateMoveCharacterMessage(teamId, characterId, currentPosition.x, currentPosition.z);
			netMessageQueue->push(message);
			lastSendPosition = currentPosition;
		}
	}
}

int Character::getId()
{
	return characterId;
}