/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetPlayer.cpp
** Implementation of the NetPlayer
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "NetPLayer.h"

NetPlayer::NetPlayer()
{
	this->tagName = "NoName";

	for(int i = 0; i < maxCharacter; ++i)
	{
		netCharacters[i] = new NetCharacter("NoName", 0, 0);
	}
}

NetPlayer::NetPlayer(std::string tagName, std::string characterNames[maxCharacter])
{
	this->tagName = "NoName";

	for(int i = 0; i < maxCharacter; ++i)
	{
		netCharacters[i] = new NetCharacter(characterNames[i], 0, 0);
	}
}

NetPlayer::~NetPlayer()
{
	for(int i = 0; i < maxCharacter; ++i)
	{
		if(netCharacters[i])
		{
			delete netCharacters[i];
		}
	}
}

void NetPlayer::moveCharacter(int id, double x, double y)
{
	netCharacters[id]->movePlayer(x, y);
}