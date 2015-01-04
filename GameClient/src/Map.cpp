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

Vector2 Map::calculateNextStep(const Vector2& targetPosition, const Vector2& currentPosition)
{
	int horizontalDiff = std::abs(targetPosition.x - currentPosition.x);
	int verticalDiff = std::abs(targetPosition.y - currentPosition.y);

	if(horizontalDiff > verticalDiff)
	{
		if(currentPosition.x < targetPosition.x)
		{
			if(isTileEmpty(rightPosition(currentPosition)))
				return rightPosition(currentPosition);
			if(isTileEmpty(upPosition(currentPosition)))
				return upPosition(currentPosition);
			if(isTileEmpty(downPosition(currentPosition)))
				return downPosition(currentPosition);
		}
		else if(currentPosition.x > targetPosition.x)
		{
			if(isTileEmpty(leftPosition(currentPosition)))
				return leftPosition(currentPosition);
			if(isTileEmpty(upPosition(currentPosition)))
				return upPosition(currentPosition);
			if(isTileEmpty(downPosition(currentPosition)))
				return downPosition(currentPosition);
		}
	}

	if(currentPosition.y < targetPosition.y)
	{
		if(isTileEmpty(upPosition(currentPosition)))
			return upPosition(currentPosition);
		if(isTileEmpty(rightPosition(currentPosition)))
			return rightPosition(currentPosition);
		if(isTileEmpty(leftPosition(currentPosition)))
			return leftPosition(currentPosition);
	}
	else if(currentPosition.y > targetPosition.y)
	{
		if(isTileEmpty(downPosition(currentPosition)))
			return downPosition(currentPosition);
		if(isTileEmpty(rightPosition(currentPosition)))
			return rightPosition(currentPosition);
		if(isTileEmpty(leftPosition(currentPosition)))
			return leftPosition(currentPosition);
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
	else
	{
		// Missile already hit
		if(oldTile->teamId != 0)
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