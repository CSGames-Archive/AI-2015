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

GameClientApplication::GameClientApplication()
{
	this->isGameOver = false;
}

GameClientApplication::~GameClientApplication()
{
	networkController->close();
	if(networkController)
	{
		delete networkController;
		networkController = NULL;
	}

	if(eventController)
	{
		delete eventController;
		eventController = NULL;
	}
}

void GameClientApplication::createScene()
{
	mCameraMan->getCamera()->setPosition(87.5, 300.0, 87.5);
	mCameraMan->getCamera()->pitch(Ogre::Radian(Ogre::Degree(-90)));
	World::getInstance().createScene();
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

	// Create world & controller
	eventController = new EventController();
	networkController = new NetworkController();
	networkController->init();
	World::getInstance().init(mSceneMgr);

	// Create the scene
	createScene();
	createFrameListener();

	//mTrayMgr->hideAll();

	return true;
};

bool GameClientApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

	//mWindow->setActive(true);

    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

	mTrayMgr->frameRenderingQueued(evt);

	if(!isGameOver)
	{
		eventController->executeAllGameEvent();

		if(World::getInstance().isGameStarted())
		{
			World::getInstance().addTime(evt.timeSinceLastFrame);
			std::string winingName = World::getInstance().getWinnerName();
			if(winingName != "")
			{
				isGameOver = true;
				showMessage("Wining: " + winingName);
				//TODO: send a endgame event
			}
		}
	}

    mCameraMan->frameRenderingQueued(evt);   // If dialog isn't up, then update the camera

	Ogre::Real ttW = 1000.0 / 60.0 - 1000.0 * evt.timeSinceLastFrame;
	if (ttW > 0)
	{
	    boost::this_thread::sleep(boost::posix_time::milliseconds(ttW));
	}

	return true;
}

void GameClientApplication::createFrameListener(void)
{
	BaseApplication::createFrameListener();
}

bool GameClientApplication::keyPressed( const OIS::KeyEvent &arg )
{
	BaseApplication::keyPressed(arg);

	if (arg.key == OIS::KC_ESCAPE)
	{
		networkController->close();
		mShutDown = true;
	}

	return true;
}

bool GameClientApplication::keyReleased( const OIS::KeyEvent &arg )
{
	BaseApplication::keyReleased(arg);

	return true;
}

bool GameClientApplication::mouseMoved( const OIS::MouseEvent &arg )
{
	BaseApplication::mouseMoved(arg);

	return true;
}

bool GameClientApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	BaseApplication::mousePressed(arg, id);

	return true;
}

bool GameClientApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	BaseApplication::mouseReleased(arg, id);

	return true;
}

void GameClientApplication::showMessage(std::string message)
{
	textElement;

	this->panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "MainPanel"));
	this->panel->setMetricsMode(Ogre::GMM_PIXELS);
	this->panel->setPosition(300, 100);
	this->panel->setDimensions(300, 120);

	this->textElement = new Ogre::TextAreaOverlayElement("Label_MainPanel");
	this->textElement->setCaption(message);
	this->textElement->setMetricsMode(Ogre::GMM_PIXELS);
	this->textElement->setAlignment(Ogre::TextAreaOverlayElement::Alignment::Center);
	this->textElement->setCharHeight(40);
	this->textElement->setFontName("SdkTrays/Caption");
	this->textElement->setColourBottom(Ogre::ColourValue(0.5, 1.0, 0.5));
	this->textElement->setColourTop(Ogre::ColourValue(1.0, 1.0, 1.0));
	this->textElement->setDimensions(300, 120);
	this->textElement->setPosition(0, 0);

	Ogre::Overlay* labelOverlay = Ogre::OverlayManager::getSingleton().create("main_label");

	this->panel->addChild(this->textElement);
	labelOverlay->add2D(this->panel);
	labelOverlay->show();
}

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
