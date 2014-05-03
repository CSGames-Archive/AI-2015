/* ---------------------------------------------------------------------------
**      _____      _____      _____   
**     /     \    /  _  \    /  _  \  
**    /  \ /  \  /  /_\  \  /  /_\  \ 
**   /    Y    \/    |    \/    |    \
**   \____|__  /\____|__  /\____|__  /
**           \/         \/         \/ 
**
** MobaActionApplication.cpp
** Main application that will run the game
**
** Author: Moba Action Alpha Team
** -------------------------------------------------------------------------*/

#include "stdafx.h"
#include "MobaActionApplication.h"

//-------------------------------------------------------------------------------------
MobaActionApplication::MobaActionApplication(void)
{
}
//-------------------------------------------------------------------------------------
MobaActionApplication::~MobaActionApplication(void)
{
}

//-------------------------------------------------------------------------------------

void MobaActionApplication::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");
}

void MobaActionApplication::createScene(void)
{
	// Set the scene's ambient light
    //mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
 
    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);

	Ogre::Plane plane;
	plane.d = 1000;
	plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

	//LogManager::getSingleton().logMessage("creating sinbad");
	mChara = new SinbadCharacterController(mCamera);
}

void MobaActionApplication::destroyScene(void)
{
		if (mChara)
        {
            delete mChara;
            mChara = 0;
        }
}

bool MobaActionApplication::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // Create the scene
    createScene();

    createFrameListener();

    return true;
};

bool MobaActionApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(mWindow->isClosed())
		return false;

	if(mShutDown)
		return false;

	//Fix for 1.9
	//Need to capture/update each device
	/*mKeyboard->capture();
	mMouse->capture();*/
	mInputContext.capture();

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mChara->addTime(evt.timeSinceLastFrame);   // if dialog isn't up, then update the character + camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }

	return true;
}

bool MobaActionApplication::keyPressed( const OIS::KeyEvent &arg )
{
	if (!mTrayMgr->isDialogVisible())
		mChara->injectKeyDown(arg);

	if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

	return true;
}

bool MobaActionApplication::keyReleased( const OIS::KeyEvent &arg )
{
	if (!mTrayMgr->isDialogVisible())
		mChara->injectKeyUp(arg);
	return true;
}

bool MobaActionApplication::mouseMoved( const OIS::MouseEvent &arg )
{
	if (!mTrayMgr->isDialogVisible())
		mChara->injectMouseMove(arg);
	return true;
}

bool MobaActionApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (!mTrayMgr->isDialogVisible())
		mChara->injectMouseDown(arg, id);
	return true;
}

bool MobaActionApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	//TODO: Add some action in here
	return true;
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        MobaActionApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
