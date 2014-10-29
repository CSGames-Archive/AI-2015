/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Team.h
** Team that control some characters
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __Team_h_
#define __Team_h_

#include "stdafx.h"

#include "Character.h"
#include "NetworkController.h"

class Team
{
private:
	NetworkController* networkController;
	Ogre::SceneManager* sceneManager;

	int id;
	char* name;
	std::map<int, Character*> netCharacters;

public:
	Team(Ogre::SceneManager* sceneManager, NetworkController* networkController, char* name, int id);
	virtual ~Team();
	void addCharacter(std::string name, int characterId, Ogre::Vector3 startingPosition);
	Character* getCharacter(int characterId);
	void addTime(Ogre::Real deltaTime);
};

#endif // #ifndef __Team_h_