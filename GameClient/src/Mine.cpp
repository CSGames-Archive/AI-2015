/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Mine.cpp
** Implementation of the mine
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "Mine.h"

Mine::Mine(Ogre::SceneNode* bodyNode)
{
	// 3d Infos
	MINE_MESH_HEIGHT = 1.5;
	this->bodyNode = bodyNode;
}

Mine::~Mine()
{
}

void Mine::setPosition(Vector2 position)
{
	Ogre::Vector3 newposition(position.x * MAP_TILE_SIZE, MINE_MESH_HEIGHT, position.y * MAP_TILE_SIZE);
	bodyNode->setPosition(newposition);
}