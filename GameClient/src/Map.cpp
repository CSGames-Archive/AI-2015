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

MapEntity::MapEntity Map::getTile(const Vector2& position)
{
	return map[position.x][position.y].type;
}

void Map::setTile(const Vector2& position, MapEntity::MapEntity value, int teamId, int characterId)
{
	map[position.x][position.y].type = value;
	map[position.x][position.y].teamId = teamId;
	map[position.x][position.y].characterId = characterId;
}

bool Map::moveUp(Vector2& currentPosition)
{
	if(currentPosition.y == MAP_HEIGHT-1)
		return false;

	++currentPosition.y;
	if( getTile(currentPosition) == MapEntity::EMPTY || getTile(currentPosition) == MapEntity::MINE)
	{
		return true;
	}
	--currentPosition.y;
	return false;
}

bool Map::moveDown(Vector2& currentPosition)
{
	if(currentPosition.y == 0)
		return false;

	--currentPosition.y;
	if( getTile(currentPosition) == MapEntity::EMPTY || getTile(currentPosition) == MapEntity::MINE)
	{
		return true;
	}
	++currentPosition.y;
	return false;
}

bool Map::moveRight(Vector2& currentPosition)
{
	if(currentPosition.x == MAP_WIDTH-1)
		return false;

	++currentPosition.x;
	if( getTile(currentPosition) == MapEntity::EMPTY || getTile(currentPosition) == MapEntity::MINE)
	{
		return true;
	}
	--currentPosition.x;
	return false;
}

bool Map::moveLeft(Vector2& currentPosition)
{
	if(currentPosition.x == 0)
		return false;

	--currentPosition.x;
	if( getTile(currentPosition) == MapEntity::EMPTY || getTile(currentPosition) == MapEntity::MINE)
	{
		return true;
	}
	++currentPosition.x;
	return false;
}

Vector2 Map::calculateSubStep(const Vector2& targetPosition, Vector2 currentPosition)
{
	int horizontalDiff = std::abs(targetPosition.x - currentPosition.x);
	int verticalDiff = std::abs(targetPosition.y - currentPosition.y);
	
	if(horizontalDiff > verticalDiff)
	{
		if(currentPosition.x < targetPosition.x)
		{
			if(moveRight(currentPosition))
				return currentPosition;
			if(moveUp(currentPosition))
				return currentPosition;
			if(moveDown(currentPosition))
				return currentPosition;
		}
		else if(currentPosition.x > targetPosition.x)
		{
			if(moveLeft(currentPosition))
				return currentPosition;
			if(moveUp(currentPosition))
				return currentPosition;
			if(moveDown(currentPosition))
				return currentPosition;
		}
	}

	if(currentPosition.y < targetPosition.y)
	{
		if(moveUp(currentPosition))
			return currentPosition;
		if(moveLeft(currentPosition))
			return currentPosition;
		if(moveRight(currentPosition))
			return currentPosition;
	}
	else if(currentPosition.y > targetPosition.y)
	{
		if(moveDown(currentPosition))
			return currentPosition;
		if(moveLeft(currentPosition))
			return currentPosition;
		if(moveRight(currentPosition))
			return currentPosition;
	}

	return currentPosition;
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