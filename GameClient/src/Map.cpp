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
	for(int x = 0; x < MAP_HEIGHT; ++x)
	{
		for(int y = 0; y < MAP_WIDTH; ++y)
		{
			map[x][x] = MapEntity::EMPTY;
		}
	}
}

MapEntity::MapEntity Map::getTile(const Vector2& position)
{
	return map[position.x][position.y];
}

void Map::setTile(const Vector2& position, MapEntity::MapEntity value)
{
	map[position.x][position.y] = value;
}

Vector2 Map::calculateSubStep(const Vector2& targetPosition, Vector2 currentPosition)
{
	int horizontalDiff = std::abs(targetPosition.x - currentPosition.x);
	int verticalDiff = std::abs(targetPosition.y - currentPosition.y);
	
	if(horizontalDiff > verticalDiff)
	{
		if(currentPosition.x < targetPosition.x)
		{
			++currentPosition.x;
			if( getTile(currentPosition) == MapEntity::EMPTY)
			{
				return currentPosition;
			}
			--currentPosition.x;
		}
		else if(currentPosition.x > targetPosition.x)
		{
			--currentPosition.x;
			if( getTile(currentPosition) == MapEntity::EMPTY)
			{
				return currentPosition;
			}
			++currentPosition.x;
		}
	}

	if(currentPosition.y < targetPosition.y)
	{
		++currentPosition.y;
		if( getTile(currentPosition) == MapEntity::EMPTY)
		{
			return currentPosition;
		}
		--currentPosition.y;
	}
	else if(currentPosition.y > targetPosition.y)
	{
		--currentPosition.y;
		if( getTile(currentPosition) == MapEntity::EMPTY)
		{
			return currentPosition;
		}
		++currentPosition.y;
	}

	return currentPosition;
}
