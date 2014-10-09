/* ---------------------------------------------------------------------------
**      _____      _____      _____   
**     /     \    /  _  \    /  _  \  
**    /  \ /  \  /  /_\  \  /  /_\  \ 
**   /    Y    \/    |    \/    |    \
**   \____|__  /\____|__  /\____|__  /
**           \/         \/         \/ 
**
** NetPlayerController.h
** Controller that manage all the network player information
**
** Author: Moba Action Alpha Team
** -------------------------------------------------------------------------*/

#ifndef __NetPlayerController_h_
#define __NetPlayerController_h_

#include "stdafx.h"
#include "NetPlayer.h"

class NetPlayerController
{
private:
	std::map<int, NetPlayer*> netPlayers;
	SceneManager* sceneMgr;
	TerrainGroup* mTerrainGroup;

public:
	NetPlayerController();
	~NetPlayerController();
	void setup(SceneManager* sceneMgr, TerrainGroup* mTerrainGroup);
	void joinPlayer(int id, Vector3 position);
	void quitPlayer(int id);
	void movePlayer(int id, Vector3 position);
	void addTime(Real deltaTime);
};

#endif // #ifndef __NetPlayerController_h_