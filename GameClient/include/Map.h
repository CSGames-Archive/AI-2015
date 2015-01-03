/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Map.h
** Map that containt the position of all entity
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __Map_h_
#define __Map_h_

#include "stdafx.h"

#include "QueueController.h"
#include "NetUtility.h"
#include <cmath>

#define MAP_TILE_SIZE 25

namespace MapEntity
{
	enum MapEntity{EMPTY, BOX, CHARACTER, CHARACTER_MINE, MINE, MISSILE};
}

namespace MapDirection
{
	enum MapDirection{UP, DOWN, LEFT, RIGHT};
}

struct Vector2
{
	int x;
	int y;

	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(Vector2 const& vector) const
	{
		if(x == vector.x && y == vector.y)
			return true;
		else
			return false;
	}
};

struct MapTile
{
	MapEntity::MapEntity type;
	int teamId;
	int characterId;

	MapTile()
	{
		type = MapEntity::EMPTY;
		teamId = 0;
		characterId = 0;
	}
};


class Map
{
private:
	MapTile map[MAP_HEIGHT][MAP_WIDTH];

	// Don't implement for singleton
	Map(Map const&);
    void operator=(Map const&);

public:
	Map();
    static Map& getInstance()
    {
        static Map instance;
        return instance;
    }

	MapEntity::MapEntity getTileType(const Vector2& position);
	MapTile* getTile(const Vector2& position);
	void setTile(const Vector2& position, MapEntity::MapEntity value, int teamId, int characterId);
	Vector2 calculateNextStep(const Vector2& currentPosition, const Vector2& targetPosition);
	bool isTileEmpty(const Vector2& position);
	bool isPositionValid(const Vector2& position);
	Vector2 leftTile(const Vector2& position);
	Vector2 rightTile(const Vector2& position);
	Vector2 upTile(const Vector2& position);
	Vector2 downTile(const Vector2& position);
	void moveCharacterTile(const Vector2& position, const Vector2& newPosition);
	Vector2 getStartingPosition(int teamId, int characterId);
};

#endif // #ifndef __Map_h_
