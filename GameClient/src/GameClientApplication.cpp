/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** GameClientAppliaction.h
** implementation of the GameClientAppliaction
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "GameClientApplication.h"

//-------------------------------------------------------------------------------------
GameClientApplication::GameClientApplication()
{
}

GameClientApplication::~GameClientApplication()
{
	netController->close();
	if(netController)
	{
		delete netController;
		netController = 0;
	}
}

//-------------------------------------------------------------------------------------

void GameClientApplication::createCamera()
{
	mCamera = mSceneMgr->createCamera("MainCamera");
}

void GameClientApplication::createScene()
{
	//TODO: Refactor with the new map
	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	// Create a Light and set its position
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);

	Ogre::Light* light2 = mSceneMgr->createLight("MainLight2");
	light2->setPosition(-20.0f, 80.0f, -50.0f);

	Ogre::Plane plane;
	plane.d = 1000;
	plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

	// create a floor mesh resource
	MeshManager::getSingleton().createPlane("floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	Plane(Vector3::UNIT_Y, 0), 1000, 1000, 10, 10, true, 1, 10, 10, Vector3::UNIT_Z);

	// create a floor entity, give it a material, and place it at the origin
	Entity* floor = mSceneMgr->createEntity("Floor", "floor");
	floor->setMaterialName("SceneMaterial/FloorSand");
	floor->setCastShadows(false);
	mSceneMgr->getRootSceneNode()->attachObject(floor);

	//TODO: Replace with the camera man
	mChara = new SinbadCharacterController(mCamera, netController);
}

void GameClientApplication::destroyScene()
{
	if (mChara)
	{
		delete mChara;
		mChara = 0;
	}
}

bool GameClientApplication::setup()
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

	netController = new NetworkController(mSceneMgr);

	netController->init();

	return true;
};

bool GameClientApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if(mWindow->isClosed())
		return false;

	if(mShutDown)
		return false;

	mWindow->setActive(true);

	//Fix for 1.9
	//Need to capture/update each device
	/*mKeyboard->capture();
	mMouse->capture();*/
	mInputContext.capture();

	mTrayMgr->frameRenderingQueued(evt);

	//TODO: some refactor with the game workflow
	if (!mTrayMgr->isDialogVisible())
	{
		mChara->addTime(evt.timeSinceLastFrame);
		netController->addTime(evt.timeSinceLastFrame);

		//TODO: some refactor with the UI
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

void GameClientApplication::createFrameListener(void)
{
	BaseApplication::createFrameListener();
}

bool GameClientApplication::keyPressed( const OIS::KeyEvent &arg )
{
	//TODO: some refactor with the gameworkflow
	if (!mTrayMgr->isDialogVisible())
		mChara->injectKeyDown(arg);

	if (arg.key == OIS::KC_ESCAPE)
	{
		//TODO: test if call in the destructor
		netController->close();
		mShutDown = true;
	}

	return true;
}

bool GameClientApplication::keyReleased( const OIS::KeyEvent &arg )
{
	if (!mTrayMgr->isDialogVisible())
		mChara->injectKeyUp(arg);
	return true;
}

bool GameClientApplication::mouseMoved( const OIS::MouseEvent &arg )
{
	if (!mTrayMgr->isDialogVisible())
		mChara->injectMouseMove(arg);
	return true;
}

bool GameClientApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (!mTrayMgr->isDialogVisible())
		mChara->injectMouseDown(arg, id);
	return true;
}

bool GameClientApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	//TODO: Add some action in here
	return true;
}

//TODO: some refactor, this code came with the sdk
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
		GameClientApplication app;

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
