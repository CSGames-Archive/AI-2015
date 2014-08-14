/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetCharacter.h
** Implementation of the NetCharacter
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "NetCharacter.h"

NetCharacter::NetCharacter(std::queue<std::string>* messageQueue)
{
	this->messageQueue = messageQueue;
}

NetCharacter::NetCharacter(std::queue<std::string>* messageQueue, std::string tagName, double x, double y)
{
	this->messageQueue = messageQueue;
	this->tagName = tagName;
	this->x = x;
	this->y = y;
}

NetCharacter::~NetCharacter()
{

}

void NetCharacter::moveCharacter(double x, double y)
{
	this->x = x;
	this->y = y;
}