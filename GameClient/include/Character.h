/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Character.h
** The Character that is controlled by the AI
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __Character_h_
#define __Character_h_

#include "stdafx.h"

#include "NetUtility.h"
#include "Map.h"

#define WALK_SPEED 50

class Character
{

private:
	// Network
	std::queue<std::string>* netMessageQueue;
	int teamId;
	int characterId;

	// Character Infos
	std::string name;
	Vector2 position;
	Vector2 targetPosition;
	Ogre::Vector3 subStepPosition;
	Ogre::Real TANK_MESH_HEIGHT;

	// 3D world components
	Ogre::SceneNode* bodyNode;

	void updateBody(Ogre::Real deltaTime);

public:
	Character(std::queue<std::string>* netMessageQueue, Ogre::SceneNode* bodyNode, std::string name, int teamId, int characterId);
	virtual ~Character();

	void addTime(Ogre::Real deltaTime);
	void setTargetPosition(int x, int z);
	int getId();
	void sendPosition();
};

#endif // #ifndef __Character_h_