/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** GameMap.h
** Map that contain all the objet
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __GameMap_h_
#define __GameMap_h_

#include <iostream>
#include <map>

#include "Player.h"

class GameMap
{
private:
	std::map<int, Player*> players;
	int yourId;
	int opponentId;

public:
	GameMap();
	~GameMap();
	void printSelf();
	void addPlayer(int id, std::string playerName, std::string characterNames[maxCharacter]);
	void quitPlayer(int id);
	void moveCharacter(int playerId, int characterId, double x, double y);
};

#endif // #ifndef __GameMap_h_