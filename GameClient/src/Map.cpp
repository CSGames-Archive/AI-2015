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
	map[0][3].type = MapEntity::BOX;
	map[0][4].type = MapEntity::BOX;
	map[0][5].type = MapEntity::BOX;

	map[8][3].type = MapEntity::BOX;
	map[8][4].type = MapEntity::BOX;
	map[8][5].type = MapEntity::BOX;

	map[3][0].type = MapEntity::BOX;
	map[4][0].type = MapEntity::BOX;
	map[5][0].type = MapEntity::BOX;

	map[3][8].type = MapEntity::BOX;
	map[4][8].type = MapEntity::BOX;
	map[5][8].type = MapEntity::BOX;

	map[3][3].type = MapEntity::BOX;
	map[5][5].type = MapEntity::BOX;
	map[3][5].type = MapEntity::BOX;
	map[5][3].type = MapEntity::BOX;
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
	int scores[4];
	Vector2 positions[4];

	// Init scores
	for(int index = 0; index < 4; ++index)
	{
		scores[index] = 0;
	}

	// Generate position
	positions[0] = leftPosition(currentPosition);
	positions[1] = rightPosition(currentPosition);
	positions[2] = upPosition(currentPosition);
	positions[3] = downPosition(currentPosition);

	//Remove old position from choice
	if(lastPosition.x < currentPosition.x)
	{
		scores[0] = MAP_WIDTH + MAP_HEIGHT -1;
	}
	else if(lastPosition.x > currentPosition.x)
	{
		scores[1] = MAP_WIDTH + MAP_HEIGHT -1;
	}
	else if(lastPosition.y > currentPosition.y)
	{
		scores[2] = MAP_WIDTH + MAP_HEIGHT -1;
	}
	else if(lastPosition.y < currentPosition.y)
	{
		scores[3] = MAP_WIDTH + MAP_HEIGHT -1;
	}

	//Check all suround tile if empty
	if(scores[0] == 0)
		scores[0] = calculateScore(positions[0], targetPosition);

	if(scores[1] == 0)
		scores[1] = calculateScore(positions[1], targetPosition);

	if(scores[2] == 0)
		scores[2] = calculateScore(positions[2], targetPosition);

	if(scores[3] == 0)
		scores[3] = calculateScore(positions[3], targetPosition);

	int lowestScore = MAP_HEIGHT + MAP_WIDTH;
	int lowestScoreIndex = -1;

	for(int index = 0; index < 4; ++index)
	{
		if(scores[index] < lowestScore)
		{
			lowestScore = scores[index];
			lowestScoreIndex = index;
		}
	}

	if(lowestScoreIndex == -1)
		return currentPosition;

	return positions[lowestScoreIndex];
}

int Map::calculateScore(const Vector2& position, const Vector2& targetPosition)
{
	if(!isTileEmpty(position))
		return MAP_HEIGHT + MAP_WIDTH;

	return std::abs(position.x - targetPosition.x) + std::abs(position.y - targetPosition.y);
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
		MissileHitEvent* newEvent = new MissileHitEvent(HitEntity::CHARACTER, oldTile->teamId, oldTile->characterId, newTile->teamId, newTile->characterId);
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
			MissileHitEvent* newEvent = new MissileHitEvent(HitEntity::CHARACTER, newTile->teamId, newTile->characterId, oldTile->teamId, oldTile->characterId);
			QueueController::getInstance().addEvent(newEvent);
		}
		else if (newTile->type == MapEntity::MINE)
		{
			MissileHitEvent* newEvent = new MissileHitEvent(HitEntity::MINE, newTile->teamId, newTile->characterId, oldTile->teamId, oldTile->characterId);
			QueueController::getInstance().addEvent(newEvent);
			setTile(newPosition, MapEntity::EMPTY, 0, 0);
		}
		else if (newTile->type == MapEntity::MISSILE)
		{
			MissileHitEvent* newEvent = new MissileHitEvent(HitEntity::MISSILE, newTile->teamId, newTile->characterId, oldTile->teamId, oldTile->characterId);
			QueueController::getInstance().addEvent(newEvent);
			setTile(newPosition, MapEntity::EMPTY, 0, 0);
		}
		else if (newTile->type == MapEntity::BOX)
		{
			MissileHitEvent* newEvent = new MissileHitEvent(HitEntity::NONE, newTile->teamId, newTile->characterId, oldTile->teamId, oldTile->characterId);
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

void Map::print()
{
	for(int y = 0; y < MAP_HEIGHT; ++y)
	{
		for(int x = 0; x < MAP_WIDTH; ++x)
		{
			std::cout << map[x][y].type;
		}
		std::cout << std::endl;
	}
}