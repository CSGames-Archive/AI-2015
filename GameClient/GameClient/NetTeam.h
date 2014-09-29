/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetTeam.h
** NetTeam that controle a character
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __NetTeam_h_
#define __NetTeam_h_

#include "stdafx.h"

#include <iostream>
#include <map>

#include "NetCharacter.h"

#define maxCharacter 2

class NetTeam
{
private:
	std::queue<std::string>* messageQueue;
	char* name;
	std::map<int, NetCharacter*> netCharacters;
	int teamId;

public:
	NetTeam(SceneManager* sceneManager, std::queue<std::string>* messageQueue, char* name, int teamId, char* characterNames[maxCharacter]);
	~NetTeam();
	void setTargetPosition(int characterId, Vector3 targetPosition);
	void addTime(Real deltaTime);
};

#endif // #ifndef __NetTeam_h_