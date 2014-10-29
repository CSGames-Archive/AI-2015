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

#include "NetworkController.h"

#define WALK_SPEED 50

class Character
{

private:
	// Network
	NetworkController* networkController;
	int teamId;
	int characterId;
	Ogre::Vector3 lastSendPosition;

	// Character Infos
	std::string name;
	Ogre::Vector3 targetPosition;

	// 3D world components
	std::string meshName;
	Ogre::SceneManager* sceneManager;
	Ogre::SceneNode* bodyNode;
	Ogre::Entity* bodyEntity;
	Ogre::Real characterHeight;

	void setupBody();
	void updateBody(Ogre::Real deltaTime);

public:
	Character(Ogre::SceneManager* sceneManager, NetworkController* networkController,
		std::string name, std::string meshName, Ogre::Vector3 startingPosition, int teamId, int characterId);
	virtual ~Character();

	void addTime(Ogre::Real deltaTime);
	void setTargetPosition(Ogre::Vector3 targetPosition);
};

#endif // #ifndef __Character_h_