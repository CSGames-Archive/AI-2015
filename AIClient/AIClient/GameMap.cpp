/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** GameMap.cpp
** Implementation of the GameMap
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "GameMap.h"

GameMap::GameMap()
{

}

GameMap::~GameMap()
{

}

void GameMap::addPlayer(int id, std::string playerName, std::string characterNames[maxCharacter])
{
	players[id] = new Player(playerName, characterNames);
}

void GameMap::quitPlayer(int id)
{
	std::map<int, Player*>::iterator it = players.find(id);
	Player* disconnectedPlayer = it->second;
	players.erase(it);
	delete disconnectedPlayer;
}

void GameMap::moveCharacter(int playerId, int characterId, double x, double y)
{
	Player* targetPlayer = players.find(playerId)->second;
	if(targetPlayer)
	{
		targetPlayer->moveCharacter(characterId, x, y);
	}
}