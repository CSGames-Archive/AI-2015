/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetPlayerController.h
** Controller that manage all the network player information
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __NetPlayerController_h_
#define __NetPlayerController_h_

#include "NetPlayer.h"
#include <iostream>

class NetPlayerController
{
private:
	std::map<int, NetPlayer*> netPlayers;

public:
	NetPlayerController();
	~NetPlayerController();

	void joinPlayer(int id, std::string playerName, std::string characterNames[maxCharacter]);
	void quitPlayer(int id);
	void moveCharacter(int playerId, int characterId, double x, double y);
};

#endif // #ifndef __NetPlayerController_h_