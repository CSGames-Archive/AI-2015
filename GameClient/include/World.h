/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** World.h
** World that contains all the information on the game
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __World_h_
#define __World_h_

#include "stdafx.h"

#include "Team.h"
#include "NetworkController.h"

class World
{
private:
	NetworkController* networkController;
	Ogre::SceneManager* sceneManager;

	std::map<int, Team*> teams;

public:
	World(Ogre::SceneManager* sceneManager, NetworkController* networkController);
	virtual ~World();

	void createScene();
	void addTeam(int id, char* teamName, char* characterNames[MAX_CHARACTER_PER_TEAM]);
	void removeTeam(int id);
	Team* getTeam(int id);
	void addTime(Ogre::Real deltaTime);
};

#endif // #ifndef __World_h_