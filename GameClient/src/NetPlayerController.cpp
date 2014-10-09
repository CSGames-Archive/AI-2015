/* ---------------------------------------------------------------------------
**      _____      _____      _____   
**     /     \    /  _  \    /  _  \  
**    /  \ /  \  /  /_\  \  /  /_\  \ 
**   /    Y    \/    |    \/    |    \
**   \____|__  /\____|__  /\____|__  /
**           \/         \/         \/ 
**
** NetPlayerController.cpp
** Controller that manage all the network information
**
** Author: Moba Action Alpha Team
** -------------------------------------------------------------------------*/

#include "stdafx.h"
#include "NetPlayerController.h"

NetPlayerController::NetPlayerController()
{
}

NetPlayerController::~NetPlayerController()
{

}

void NetPlayerController::setup(SceneManager* sceneMgr, TerrainGroup* mTerrainGroup)
{
	this->sceneMgr = sceneMgr;
	this->mTerrainGroup = mTerrainGroup;
}

void NetPlayerController::joinPlayer(int id, Vector3 position)
{
	char numstr[21]; // enough to hold all numbers up to 64-bits
	sprintf(numstr, "%d", id);
	std::string tagName = "netplayer";
	tagName += numstr;

	netPlayers[id] = new NetPlayer(sceneMgr, mTerrainGroup, tagName, "Sinbad.mesh", position);
}

void NetPlayerController::quitPlayer(int id)
{
	std::map<int, NetPlayer*>::iterator it = netPlayers.find(id);
	NetPlayer* disconnectedPlayer = it->second;
	netPlayers.erase(it);
	delete disconnectedPlayer;
}

void NetPlayerController::movePlayer(int id, Vector3 position)
{
	netPlayers.find(id)->second->updateDestination(position);
}

void NetPlayerController::addTime(Real deltaTime)
{
	typedef std::map<int, NetPlayer*>::iterator it_type;
	for(it_type iterator = netPlayers.begin(); iterator != netPlayers.end(); iterator++)
	{
		iterator->second->addTime(deltaTime);
	}
}