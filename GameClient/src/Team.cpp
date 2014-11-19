/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Team.cpp
** Implementation of the NetTeam
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "Team.h"

Team::Team(std::string name, int teamId)
{
	this->name = name;
	this->id = teamId;
	characterCount = 0;
}

Team::~Team()
{
	for(int i = 0; i < characterCount; ++i)
	{
		if(characters[i])
		{
			delete characters[i];
		}
	}
}

void Team::addCharacter(Character* character)
{
	characters[characterCount++] = character;
}

Character* Team::getCharacter(int characterId)
{
	if(characterId < characterCount)
		return characters[characterId];
	else
		return NULL;
}

void Team::addTime(Ogre::Real deltaTime)
{
	for(int i = 0; i < characterCount; ++i)
	{
		if(characters[i])
		{
			characters[i]->addTime(deltaTime);
		}
	}
}

int Team::getId()
{
	return id;
}