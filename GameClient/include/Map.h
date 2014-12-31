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

#include <cmath>

#define MAP_TILE_SIZE 25

namespace MapEntity
{
	enum MapEntity{EMPTY, BOX, CHARACTER, CHARACTER_MINE, MINE, MISSILE};
}

struct Vector2
{
	int x;
	int y;

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

	MapEntity::MapEntity getTile(const Vector2& position);
	void setTile(const Vector2& position, MapEntity::MapEntity value, int teamId, int characterId);
	Vector2 calculateSubStep(const Vector2& currentPosition, Vector2 targetPosition);
	bool moveUp(Vector2& currentPosition);
	bool moveDown(Vector2& currentPosition);
	bool moveLeft(Vector2& currentPosition);
	bool moveRight(Vector2& currentPosition);
	Vector2 getStartingPosition(int teamId, int characterId);
};

#endif // #ifndef __Map_h_
