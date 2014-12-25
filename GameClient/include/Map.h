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

#define MAP_SQUARE_SIZE 50

namespace MapEntity
{
	enum MapEntity{EMPTY, BOX, CHARACTER};
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

class Map
{
private:
	MapEntity::MapEntity map[MAP_HEIGHT][MAP_WIDTH];

public:
	Map();
	virtual ~Map() {}

	MapEntity::MapEntity getSquare(Vector2 postion);
	static Vector2 calculateSubStep(const Vector2& currentPosition, Vector2& targetPosition);
};

#endif // #ifndef __Map_h_