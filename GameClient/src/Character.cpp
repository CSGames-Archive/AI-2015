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
	TANK_MESH_HEIGHT = 2.5;
	this->bodyNode = bodyNode;
	this->position = Map::getInstance().getStartingPosition(teamId, characterId);
	this->targetPosition = this->position;
	Ogre::Vector3 startingVector(this->position.x*MAP_SQUARE_SIZE, TANK_MESH_HEIGHT, this->position.y*MAP_SQUARE_SIZE);
	this->bodyNode->setPosition(startingVector);
	this->subStepPosition = startingVector;

	// Character Infos
	this->name = name;
}

Character::~Character()
{
}

void Character::addTime(Ogre::Real deltaTime)
{
	updateBody(deltaTime);
}

void Character::setTargetPosition(int x, int z)
{
	if(x > -1 && x < MAP_HEIGHT)
	{
		this->targetPosition.x = x;
	}

	if(z > -1 && z < MAP_WIDTH)
	{
		this->targetPosition.y = z;
	}
}

void Character::updateBody(Ogre::Real deltaTime)
{
	if(bodyNode != NULL)
	{
		Ogre::Vector3 currentPosition = bodyNode->getPosition();
		Ogre::Vector3 goalDirection = subStepPosition - currentPosition;
		
		if(goalDirection.length() < Ogre::Real(1.0))
		{
			if(position == targetPosition)
			{
				goalDirection = Ogre::Vector3::ZERO;
			}
			else
			{
				Vector2 newPosition = Map::getInstance().calculateSubStep(targetPosition, position);

				if(newPosition == position)
				{
					goalDirection = Ogre::Vector3::ZERO;
				}
				else
				{
					Map::getInstance().setTile(position, MapEntity::EMPTY);
					Map::getInstance().setTile(newPosition, MapEntity::CHARACTER);
					position = newPosition;

					std::string message = NetUtility::generateMoveCharacterMessage(teamId, characterId, position.x, position.y);
					netMessageQueue->push(message);

					subStepPosition = Ogre::Vector3(Ogre::Real(position.x*MAP_SQUARE_SIZE), currentPosition.y, Ogre::Real(position.y*MAP_SQUARE_SIZE));
					goalDirection = subStepPosition - currentPosition;
				}
			}
		}

		if(goalDirection != Ogre::Vector3::ZERO)
		{
			// Calculate direction
			goalDirection.normalise();
			Ogre::Quaternion currentDirection = bodyNode->getOrientation().zAxis().getRotationTo(goalDirection);

			// Find the rotation in yaw
			Ogre::Real yawToGoal = currentDirection.getYaw().valueDegrees();

			bodyNode->yaw(Ogre::Degree(yawToGoal));

			bodyNode->translate(0, 0, deltaTime * WALK_SPEED, Ogre::Node::TS_LOCAL);
		}
	}
}

int Character::getId()
{
	return characterId;
}

void Character::sendPosition()
{
	std::string message = NetUtility::generateMoveCharacterMessage(teamId, characterId, position.x, position.y);
	netMessageQueue->push(message);
}