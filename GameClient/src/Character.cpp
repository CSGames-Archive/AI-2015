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

Character::Character(Ogre::SceneNode* bodyNode, Mine* mine, Missile* missile, TextOverlay* nameOverlay, TextOverlay* lifeOverlay, std::string name, int teamId, int characterId)
{
	// Network
	this->teamId = teamId;
	this->characterId = characterId;

	// 3d Infos
	TANK_MESH_HEIGHT = 2.5;
	this->bodyNode = bodyNode;
	this->position = Map::getInstance().getStartingPosition(teamId, characterId);
	Map::getInstance().setTile(this->position, MapEntity::CHARACTER, this->teamId, this->characterId);

	this->targetPosition = this->position;
	Ogre::Vector3 startingVector(this->position.x*MAP_TILE_SIZE, TANK_MESH_HEIGHT, this->position.y*MAP_TILE_SIZE);
	this->bodyNode->setPosition(startingVector);
	this->subStepPosition = startingVector;

	// Character Infos
	this->name = name;
	this->mine = mine;
	this->missile = missile;
	this->nameOverlay = nameOverlay;
	this->lifeOverlay = lifeOverlay;

	this->askForMine = false;
	this->askForMissile = false;
	this->timeToWait = 0.0;
}

Character::~Character()
{
	if(mine)
		delete mine;

	if(missile)
		delete missile;

	if(nameOverlay)
		delete nameOverlay;

	if(lifeOverlay)
		delete lifeOverlay;
}

void Character::addTime(Ogre::Real deltaTime, Ogre::Camera* camera)
{
	updateBody(deltaTime);
	missile->addTime(deltaTime);
	nameOverlay->update(camera);
	lifeOverlay->update(camera);
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
			if(askForMine)
			{
				dropMine();
			}
			if(askForMissile)
			{
				throwMissile();
			}

			if(timeToWait > 0)
			{
				timeToWait -= deltaTime;
				goalDirection = Ogre::Vector3::ZERO;
			}
			else if(position == targetPosition)
			{
				goalDirection = Ogre::Vector3::ZERO;
			}
			else
			{
				Vector2 newPosition = Map::getInstance().calculateNextStep(targetPosition, position);

				if(newPosition == position)
				{
					goalDirection = Ogre::Vector3::ZERO;
				}
				else
				{
					Map::getInstance().moveCharacterTile(position, newPosition);
					position = newPosition;
					sendPosition();

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
	QueueController::getInstance().addMessage(message);
}

bool Character::isMineReady()
{
	return !mine->isVisible();
}

void Character::askMine()
{
	askForMine = true;
	mine->setPosition(position);
}

void Character::dropMine()
{
	askForMine = false;
	if(mine && isMineReady())
	{
		Map::getInstance().setTile(position, MapEntity::CHARACTER_MINE, teamId, characterId);
		mine->setVisible(true);
	}
}

void Character::throwMissile()
{
	askForMissile = false;
	if(missile && isMissileReady() && timeToWait <= 0)
	{
		timeToWait = 1.0;
		missile->launch();

		Ogre::Real targetDegree = Ogre::Real(MapDirection::DirectionToDegree(missile->getDirection()));
		Ogre::Real currentDegree = bodyNode->getOrientation().getYaw().valueDegrees();
		// The front of the mesh is 90 degree off
		Ogre::Degree degreeToYaw = Ogre::Degree(targetDegree - currentDegree - 90.0);
		bodyNode->yaw(degreeToYaw, Ogre::Node::TS_WORLD);
	}
}

Mine* Character::getMine()
{
	return mine;
}

bool Character::isMissileReady()
{
	return !missile->isVisible();
}

void Character::askMissile(int direction)
{
	askForMissile = true;
	if(missile && isMissileReady())
	{
		missile->init(position,static_cast<MapDirection::MapDirection>(direction));
	}
}

Missile* Character::getMissile()
{
	return missile;
}