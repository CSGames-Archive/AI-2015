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
#include "QueueController.h"

class World
{
private:
	// TODO: find better place
	char* TANK_MESH_NAME;
	char* MINE_MESH_NAME;
	char* MISSILE_MESH_NAME;
	Team* teams[MAX_TEAM];
	int teamCount;

	Ogre::SceneManager* sceneManager;

	// Don't implement for singleton
	World(World const&);
    void operator=(World const&);

public:
	World();
	virtual ~World();
	void init(Ogre::SceneManager* sceneManager);

	static World& getInstance()
    {
        static World instance;
        return instance;
    }

	void createScene();
	void addTeam(int teamId, std::string teamName, std::string characterNames[MAX_CHARACTER_PER_TEAM]);
	void removeTeam(int teamId);
	Team* getTeam(int teamId);
	void addTime(Ogre::Real deltaTime);
	void gameStart();
	void sendAllPosition();
	void mineHit(int hitPlayerId, int hitCharacterId, int originPlayerId, int originCharacterId);
	void missileHitCharacter(int hitPlayerId, int hitCharacterId, int originPlayerId, int originCharacterId);
	void missileHitMine(int hitPlayerId, int hitCharacterId, int originPlayerId, int originCharacterId);
};

#endif // #ifndef __World_h_