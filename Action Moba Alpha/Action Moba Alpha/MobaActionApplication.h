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
#include "BaseApplication.h"
#include "SinbadCharacterController.h"

class MobaActionApplication : public BaseApplication
{
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

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	SinbadCharacterController* mChara;
};

#endif // #ifndef __MobaActionApplication_h_
