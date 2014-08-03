/* ---------------------------------------------------------------------------
**      _____      _____      _____   
**     /     \    /  _  \    /  _  \  
**    /  \ /  \  /  /_\  \  /  /_\  \ 
**   /    Y    \/    |    \/    |    \
**   \____|__  /\____|__  /\____|__  /
**           \/         \/         \/ 
**
** MobaActionApplication.h
** Main application that will run the game
**
** Author: Moba Action Alpha Team
** -------------------------------------------------------------------------*/

#ifndef __MobaActionApplication_h_
#define __MobaActionApplication_h_

#include "stdafx.h"

#include "NetworkController.h"

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include "BaseApplication.h"
#include "SinbadCharacterController.h"
#include "NPC.h"
#include "NetPlayerController.h"

class MobaActionApplication : public BaseApplication
{
private:
	Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
    bool mTerrainsImported;
	OgreBites::Label* mInfoLabel;

	void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);

	// Networking
	NetworkController netController;
	NetPlayerController netPlayerController;

public:
    MobaActionApplication(void);
    virtual ~MobaActionApplication(void);

protected:
    virtual void createScene(void);
    virtual void destroyScene(void);
	virtual bool setup();
	void MobaActionApplication::createCamera(void);

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual void createFrameListener(void);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	
	SinbadCharacterController* mChara;
	NPCController* mNPC;
};

#endif // #ifndef __MobaActionApplication_h_
