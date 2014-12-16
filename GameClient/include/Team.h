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

class Team
{
private:
	int id;
	std::string name;
	Character* characters[MAX_CHARACTER_PER_TEAM];
	int characterCount;

public:
	Team(std::string name, int id);
	virtual ~Team();

	void addCharacter(Character* character);
	Character* getCharacter(int characterId);
	void addTime(Ogre::Real deltaTime);
	int getId();
};

#endif // #ifndef __Team_h_