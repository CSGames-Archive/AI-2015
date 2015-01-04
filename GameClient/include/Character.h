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
#include "Mine.h"
#include "Missile.h"
#include "QueueController.h"

class Character
{

private:
	// Network
	int teamId;
	int characterId;

	// Character Infos
	std::string name;
	Vector2 position;
	Vector2 targetPosition;
	Ogre::Vector3 subStepPosition;
	Ogre::Real TANK_MESH_HEIGHT;
	bool askForMine;
	bool askForMissile;
	Ogre::Real timeToWait;

	// 3D world components
	Ogre::SceneNode* bodyNode;
	Mine* mine;
	Missile* missile;

	void updateBody(Ogre::Real deltaTime);

public:
	Character(Ogre::SceneNode* bodyNode, Mine* mine, Missile* missile, std::string name, int teamId, int characterId);
	virtual ~Character();

	void addTime(Ogre::Real deltaTime);
	void setTargetPosition(int x, int z);
	int getId();
	std::string getName();
	void sendPosition();

	bool isMineReady();
	void dropMine();
	Mine* getMine();
	void askMine();

	bool isMissileReady();
	void askMissile(int direction);
	void throwMissile();
	Missile* getMissile();
};

#endif // #ifndef __Character_h_