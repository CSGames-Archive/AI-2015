/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Map.cpp
** Implementation of the Map
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "Map.h"

Map::Map()
{
	//TODO: load from a file
	map[4][0].type = MapEntity::BOX;
	map[7][4].type = MapEntity::BOX;
	map[0][4].type = MapEntity::BOX;
	map[4][7].type = MapEntity::BOX;

	map[4][4].type = MapEntity::BOX;
	map[3][3].type = MapEntity::BOX;
	map[3][4].type = MapEntity::BOX;
	map[4][3].type = MapEntity::BOX;
}

MapEntity::MapEntity Map::getTileType(const Vector2& position)
{
	return map[position.x][position.y].type;
}

MapTile* Map::getTile(const Vector2& position)
{
	return &map[position.x][position.y];
}

void Map::setTile(const Vector2& position, MapEntity::MapEntity value, int teamId, int characterId)
{
	map[position.x][position.y].type = value;
	map[position.x][position.y].teamId = teamId;
	map[position.x][position.y].characterId = characterId;
}

bool Map::isTileEmpty(const Vector2& position)
{
	if(!isPositionValid(position))
		return false;

	MapEntity::MapEntity tileType = getTileType(position);
	if( tileType == MapEntity::EMPTY || tileType == MapEntity::MINE || tileType == MapEntity::MISSILE)
	{
		return true;
	}
	return false;
}

bool Map::isPositionValid(const Vector2& position)
{
	if(position.x > -1 && position.x < MAP_WIDTH &&
		position.y > -1 && position.y < MAP_HEIGHT)
	{
		return true;
	}
	return false;
}

Vector2 leftPosition(const Vector2& position)
{
	return Vector2(position.x-1, position.y);
}

Vector2 rightPosition(const Vector2& position)
{
	return Vector2(position.x+1, position.y);
}

Vector2 upPosition(const Vector2& position)
{
	return Vector2(position.x, position.y+1);
}

Vector2 downPosition(const Vector2& position)
{
	return Vector2(position.x, position.y-1);
}

Vector2 Map::calculateNextStep(const Vector2& targetPosition, const Vector2& currentPosition, const Vector2& lastPosition)
{
	bool checkLeft = false, checkRight = false, checkUp = false, checkDown = false;

	//Remove old position from choice
	if(lastPosition.x > currentPosition.x)
	{
		checkRight = true;
	}
	else if(lastPosition.x < currentPosition.x)
	{
		checkLeft = true;
	}
	else if(lastPosition.y > currentPosition.y)
	{
		checkUp = true;
	}
	else if(lastPosition.y < currentPosition.y)
	{
		checkDown = true;
	}

	//Check all suround tile if empty
	if(!checkLeft && !isTileEmpty(leftPosition(currentPosition)))
		checkLeft = true;
	if(!checkRight && !isTileEmpty(rightPosition(currentPosition)))
		checkRight = true;
	if(!checkDown && !isTileEmpty(downPosition(currentPosition)))
		checkDown = true;
	if(!checkUp && !isTileEmpty(upPosition(currentPosition)))
		checkUp = true;

	//Calculate the difference between the target and the current position
	int horizontalDiff = std::abs(targetPosition.x - currentPosition.x);
	int verticalDiff = std::abs(targetPosition.y - currentPosition.y);

	//If there's more horizontal distance to go or if we check all the other way
	if(horizontalDiff > verticalDiff || (checkDown && checkUp) )
	{
		//If we need to go to the right or if we check all other way
		if(currentPosition.x < targetPosition.x || (checkDown && checkUp && checkLeft))
		{
			//If rigth is empty
			if(!checkRight)
				return rightPosition(currentPosition);
		}
		//If we need to go to the left or if we check all other way
		if(currentPosition.x > targetPosition.x || (checkDown && checkUp && checkRight))
		{
			//If left empty
			if(!checkLeft)
				return leftPosition(currentPosition);
		}
	}
	//If we need to go up or if we check all other way
	if(currentPosition.y < targetPosition.y || (checkDown && checkRight && checkLeft))
	{
		if(!checkUp)
			return upPosition(currentPosition);
	}
	//If we need to go down or if we check all other way
	if(currentPosition.y > targetPosition.y || (checkUp && checkRight && checkLeft))
	{
		if(!checkDown)
			return downPosition(currentPosition);
	}

	return currentPosition;
}

void Map::moveCharacterTile(const Vector2& position, const Vector2& newPosition)
{
	MapTile* oldTile = getTile(position);
	MapTile* newTile = getTile(newPosition);

	if(newTile->type == MapEntity::MINE)
	{
		MineHitEvent* newEvent = new MineHitEvent(oldTile->teamId, oldTile->characterId, newTile->teamId, newTile->characterId);
		QueueController::getInstance().addEvent(newEvent);
	}
	else if (newTile->type == MapEntity::MISSILE)
	{
		MissileHitEvent* newEvent = new MissileHitEvent(MissileHitEvent::HitEntity::CHARACTER, oldTile->teamId, oldTile->characterId, newTile->teamId, newTile->characterId);
		QueueController::getInstance().addEvent(newEvent);
	}

	setTile(newPosition, MapEntity::CHARACTER, oldTile->teamId, oldTile->characterId);

	if(oldTile->type == MapEntity::CHARACTER_MINE)
	{
		oldTile->type = MapEntity::MINE;
	}
	else
	{
		setTile(position, MapEntity::EMPTY, 0, 0);
	}
}

void Map::moveMissileTile(const Vector2& position, const Vector2& newPosition)
{
	MapTile* oldTile = getTile(position);
	MapTile* newTile = getTile(newPosition);

	if(oldTile->teamId != 0)
	{
		if (newTile->type == MapEntity::CHARACTER || newTile->type == MapEntity::CHARACTER_MINE)
		{
			MissileHitEvent* newEvent = new MissileHitEvent(MissileHitEvent::HitEntity::CHARACTER, newTile->teamId, newTile->characterId, oldTile->teamId, oldTile->characterId);
			QueueController::getInstance().addEvent(newEvent);
		}
		else if (newTile->type == MapEntity::MINE)
		{
			MissileHitEvent* newEvent = new MissileHitEvent(MissileHitEvent::HitEntity::MINE, newTile->teamId, newTile->characterId, oldTile->teamId, oldTile->characterId);
			QueueController::getInstance().addEvent(newEvent);
			setTile(newPosition, MapEntity::EMPTY, 0, 0);
		}
		else if (newTile->type == MapEntity::MISSILE)
		{
			MissileHitEvent* newEvent = new MissileHitEvent(MissileHitEvent::HitEntity::MISSILE, newTile->teamId, newTile->characterId, oldTile->teamId, oldTile->characterId);
			QueueController::getInstance().addEvent(newEvent);
			setTile(newPosition, MapEntity::EMPTY, 0, 0);
		}
		else if (newTile->type == MapEntity::BOX)
		{
			MissileHitEvent* newEvent = new MissileHitEvent(MissileHitEvent::HitEntity::NONE, newTile->teamId, newTile->characterId, oldTile->teamId, oldTile->characterId);
			QueueController::getInstance().addEvent(newEvent);
		}
		else
		{
			setTile(newPosition, MapEntity::MISSILE, oldTile->teamId, oldTile->characterId);
		}
	}

	if(oldTile->type != MapEntity::CHARACTER && oldTile->type != MapEntity::CHARACTER_MINE)
	{
		setTile(position, MapEntity::EMPTY, 0, 0);
	}
}

Vector2 Map::getStartingPosition(int teamId, int characterId)
{
	Vector2 startingPosition;
	startingPosition.x = 0;
	startingPosition.y = 0;
	//TODO: refactor for more than 2 team
	if(teamId == 2)
	{
		if(characterId == 0)
		{
			startingPosition.x = 0;
			startingPosition.y = 0;
		}
		else if(characterId == 1)
		{
			startingPosition.x = MAP_WIDTH-1;
			startingPosition.y = MAP_WIDTH-1;
		}
	}
	else if(teamId == 3)
	{
		if(characterId == 0)
		{
			startingPosition.x = 0;
			startingPosition.y = MAP_WIDTH-1;
		}
		else if(characterId == 1)
		{
			startingPosition.x = MAP_WIDTH-1;
			startingPosition.y = 0;
		}
	}
	return startingPosition;
}