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

#include "stdafx.h"

#include "NetTeam.h"

#define MAX_PLAYER 2

class NetPlayerController
{
private:
	std::queue<std::string>* messageQueue;
	std::map<int, NetTeam*> netTeams;
	SceneManager* sceneManager;

public:
	NetPlayerController(SceneManager* sceneManager, std::queue<std::string>* messageQueue);
	~NetPlayerController();

	void addPlayer(int id, char* playerName, char* characterNames[maxCharacter]);
	void quitPlayer(int id);
	void setTargetPosition(int teamId, int characterId, double x, double y);
	void addTime(Real deltaTime);
};

#endif // #ifndef __NetPlayerController_h_