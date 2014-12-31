/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Character.cpp
** Implementation of the Character
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
	Ogre::Vector3 startingVector(this->position.x*MAP_TILE_SIZE, TANK_MESH_HEIGHT, this->position.y*MAP_TILE_SIZE);
	this->bodyNode->setPosition(startingVector);
	this->subStepPosition = startingVector;

	// Character Infos
	this->name = name;
	this->mine = NULL;
}

Character::~Character()
{
	if(mine)
		delete mine;
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
					if(Map::getInstance().getTile(position) == MapEntity::CHARACTER_MINE)
					{
						Map::getInstance().setTile(position, MapEntity::MINE, teamId, characterId);
					}
					else
					{
						Map::getInstance().setTile(position, MapEntity::EMPTY, 0, 0);
					}

					Map::getInstance().setTile(newPosition, MapEntity::CHARACTER, teamId, characterId);
					position = newPosition;

					std::string message = NetUtility::generateMoveCharacterMessage(teamId, characterId, position.x, position.y);
					netMessageQueue->push(message);

					subStepPosition = Ogre::Vector3(Ogre::Real(position.x*MAP_TILE_SIZE), currentPosition.y, Ogre::Real(position.y*MAP_TILE_SIZE));
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

			bodyNode->translate(0, 0, deltaTime * CHARACTER_WALK_SPEED, Ogre::Node::TS_LOCAL);
		}
	}
}

int Character::getId()
{
	return characterId;
}

std::string Character::getName()
{
	return name;
}

void Character::sendPosition()
{
	std::string message = NetUtility::generateMoveCharacterMessage(teamId, characterId, position.x, position.y);
	netMessageQueue->push(message);
}

bool Character::isMineReady()
{
	return (!this->mine)?true:false;
}

void Character::dropMine(Mine* mine)
{
	if(this->mine)
	{
		// Generate destroy event, not supposed to happen
	}

	mine->setPosition(position);
	this->mine = mine;

	Map::getInstance().setTile(position, MapEntity::CHARACTER_MINE, teamId, characterId);
}