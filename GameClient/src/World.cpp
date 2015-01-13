/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** World.cpp
** Implementation of the World
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "World.h"

#include <OgreOverlayManager.h>

World::World()
{
	TANK_MESH_NAME = "Tank.mesh";
	MINE_MESH_NAME = "Mine.mesh";
	MISSILE_MESH_NAME = "Missile.mesh";

	this->sceneManager = NULL;
	teamCount = 0;

	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		teams[i] = NULL;
	}

	this->gameStarted = false;
}

World::~World()
{
	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		if(teams[i])
		{
			delete teams[i];
		}
	}
}

void World::init(Ogre::SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
}

void World::createScene()
{
	// Set the scene's ambient light
	sceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	// Create a Light and set its position
	Ogre::Light* light = sceneManager->createLight("MainLight");
	light->setPosition(Ogre::Real(-2.0*MAP_TILE_SIZE), 80.0, Ogre::Real(-2.0*MAP_TILE_SIZE));

	light = sceneManager->createLight("MainLight2");
	light->setPosition(Ogre::Real(-2.0*MAP_TILE_SIZE), 80.0, Ogre::Real(9.0*MAP_TILE_SIZE));

	light = sceneManager->createLight("MainLight3");
	light->setPosition(Ogre::Real(9.0*MAP_TILE_SIZE), 80.0f, Ogre::Real(-2.0*MAP_TILE_SIZE));

	light = sceneManager->createLight("MainLight4");
	light->setPosition(Ogre::Real(9.0*MAP_TILE_SIZE), 80.0f, Ogre::Real(9.0*MAP_TILE_SIZE));

	sceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);

	// create a floor mesh resource
	Ogre::MeshManager::getSingleton().createPlane("floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
												  Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 1000.0, 1000.0,
												  10, 10, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);

	// create a floor entity, give it a material, and place it at the origin
	Ogre::SceneNode* floorNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* floor = sceneManager->createEntity("Floor", "floor");
	floor->setMaterialName("SceneMaterial/FloorSand");
	floor->setCastShadows(false);
	floorNode->attachObject(floor);
	floorNode->setPosition(87.5, 0.0, 87.5);

	labelOverlay = Ogre::OverlayManager::getSingleton().create("labelOverlay");

	generateMapDelimiter();
}

void World::addTeam(int teamId, std::string teamName, std::string characterNames[MAX_CHARACTER_PER_TEAM])
{
	Team* team = new Team(teamName, teamId);
	teams[teamCount++] = team;

	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		Ogre::SceneNode* bodyNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Entity* entity = sceneManager->createEntity(characterNames[i], TANK_MESH_NAME);
		bodyNode->attachObject(entity);

		std::string mineName = "mine_" + characterNames[i];
		Ogre::SceneNode* mineNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Entity* mineEntity = sceneManager->createEntity(mineName, MINE_MESH_NAME);
		mineNode->attachObject(mineEntity);
		mineNode->setScale(Ogre::Vector3(2.0, 2.0, 2.0));
		mineNode->setVisible(false);

		std::string missileName = "missile_" + characterNames[i];
		Ogre::SceneNode* missileNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Entity* missileEntity = sceneManager->createEntity(missileName, MISSILE_MESH_NAME);
		missileNode->attachObject(missileEntity);
		missileNode->setVisible(false);

		Mine* mine = new Mine(mineNode, mineName);
		Missile* missile = new Missile(missileNode, missileName, teamId, i);
		TextOverlay* nameOverlay = new TextOverlay(labelOverlay, characterNames[i], characterNames[i], bodyNode, sceneManager->getCamera("PlayerCam")->getViewport());
		TextOverlay* lifeOverlay = new TextOverlay(labelOverlay, "Life: ", "Life_" + characterNames[i], bodyNode, sceneManager->getCamera("PlayerCam")->getViewport(), Ogre::Vector3::UNIT_Y*15.0);
		lifeOverlay->setColors(Ogre::ColourValue(1.0, 0.5, 0.5), Ogre::ColourValue(1.0, 1.0, 1.0));

		Character* character = new Character(bodyNode, mine, missile, nameOverlay, lifeOverlay, characterNames[i], teamId, i);
		team->addCharacter(character);
	}

	if(teamCount == MAX_TEAM)
	{
		generateMap();
		gameStart();
		sendAllPosition();
	}
}

void World::removeTeam(int teamId)
{
	Team* team = getTeam(teamId);
	if(team)
	{
		delete team;
	}
}

Team* World::getTeam(int teamId)
{
	for(int i = 0; i < MAX_TEAM; ++i)
	{
		if(teams[i] && teams[i]->getId() == teamId)
		{
			return teams[i];
		}
	}
	return NULL;
}

void World::addTime(Ogre::Real deltaTime)
{
	for(int i = 0; i < MAX_TEAM; ++i)
	{
		if(teams[i])
		{
			teams[i]->addTime(deltaTime, sceneManager->getCamera("PlayerCam"));
		}
	}
}

void World::gameStart()
{
	gameStarted = true;

	char numstr[21]; // Enough to hold all numbers up to 64-bits
	std::string message = "Game:GameStart";

	message += ":";
	sprintf(numstr, "%d", MAP_WIDTH);
	message += numstr;

	message += ":";
	sprintf(numstr, "%d", MAP_HEIGHT);
	message += numstr;

	message += ":";
	sprintf(numstr, "%d", MAX_TEAM);
	message += numstr;

	message += ":";
	sprintf(numstr, "%d", MAX_CHARACTER_PER_TEAM);
	message += numstr;

	for(int i = 0; i < MAX_TEAM; ++i)
	{
		message += ":";
		sprintf(numstr, "%d", teams[i]->getId());
		message += numstr;
	}
	QueueController::getInstance().addMessage(message);
}

void World::sendAllPosition()
{
	for(int teamIndex = 0; teamIndex < MAX_TEAM; ++teamIndex)
	{
		for(int characterIndex = 0; characterIndex < MAX_CHARACTER_PER_TEAM; ++characterIndex)
		{
			teams[teamIndex]->getCharacter(characterIndex)->sendPosition();
		}
	}
}

void World::mineHit(int hitPlayerId, int hitCharacterId, int originPlayerId, int originCharacterId)
{
	getTeam(originPlayerId)->getCharacter(originCharacterId)->getMine()->setVisible(false);
	getTeam(hitPlayerId)->getCharacter(hitCharacterId)->hit();
}

void World::missileHitCharacter(int hitPlayerId, int hitCharacterId, int originPlayerId, int originCharacterId)
{
	getTeam(hitPlayerId)->getCharacter(hitCharacterId)->hit();
	getTeam(originPlayerId)->getCharacter(originCharacterId)->getMissile()->setVisible(false);
}

void World::missileHitMine(int hitPlayerId, int hitCharacterId, int originPlayerId, int originCharacterId)
{
	getTeam(originPlayerId)->getCharacter(originCharacterId)->getMissile()->setVisible(false);
	getTeam(hitPlayerId)->getCharacter(hitCharacterId)->getMine()->setVisible(false);
}

void World::missileHitMissile(int hitPlayerId, int hitCharacterId, int originPlayerId, int originCharacterId)
{
	getTeam(originPlayerId)->getCharacter(originCharacterId)->getMissile()->setVisible(false);
	getTeam(hitPlayerId)->getCharacter(hitCharacterId)->getMissile()->setVisible(false);
}

void World::generateMap()
{
	Map& map = Map::getInstance();
	Ogre::Vector3 scaleVector(1.5, 1.5, 1.5);
	char numstr[21]; // Enough to hold all numbers up to 64-bits
	sprintf(numstr, "%d", MAX_TEAM);

	for(int x = 0; x < MAP_WIDTH; ++x)
	{
		for(int y = 0; y < MAP_HEIGHT; ++y)
		{
			if(map.getTileType(Vector2(x, y)) == MapEntity::BOX)
			{
				sprintf(numstr, "%d%d", x, y);
				std::string name = "box_";
				name += numstr;

				Ogre::SceneNode* crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
				Ogre::Entity* crate = sceneManager->createEntity(name, "WoodCrate.mesh");
				crateNode->attachObject(crate);
				crateNode->setScale(scaleVector);
				crateNode->setPosition(Ogre::Real(x*MAP_TILE_SIZE), 7.5, Ogre::Real(y*MAP_TILE_SIZE));

				std::string message = NetUtility::generateUpdateBoxMessage(x, y);
				QueueController::getInstance().addMessage(message);
			}
		}
	}
}

void World::generateMapDelimiter()
{
	char numstr[21]; // Enough to hold all numbers up to 64-bits
	Ogre::Vector3 scaleVector(2.5, 2.5, 2.5);

	for(int x = -1; x < MAP_WIDTH + 1; ++x)
	{
		sprintf(numstr, "%d", x);
		std::string name = "delimiter_down_";
		name += numstr;

		Ogre::SceneNode* crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Entity* crate = sceneManager->createEntity(name, "WoodCrate.mesh");
		crateNode->attachObject(crate);
		crateNode->setScale(scaleVector);
		crateNode->setPosition(Ogre::Real(x*MAP_TILE_SIZE), 12.5, -MAP_TILE_SIZE);

		sprintf(numstr, "%d", x);
		name = "delimiter_up_";
		name += numstr;

		crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		crate = sceneManager->createEntity(name, "WoodCrate.mesh");
		crateNode->attachObject(crate);
		crateNode->setScale(scaleVector);
		crateNode->setPosition(Ogre::Real(x*MAP_TILE_SIZE), 12.5, Ogre::Real(MAP_TILE_SIZE*MAP_HEIGHT));
	}

	for(int y = 0; y < MAP_HEIGHT; ++y)
	{
		sprintf(numstr, "%d", y);
		std::string name = "delimiter_left_";
		name += numstr;

		Ogre::SceneNode* crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Entity* crate = sceneManager->createEntity(name, "WoodCrate.mesh");
		crateNode->attachObject(crate);
		crateNode->setScale(scaleVector);
		crateNode->setPosition(-Ogre::Real(MAP_TILE_SIZE), 12.5, Ogre::Real(y*MAP_TILE_SIZE));

		sprintf(numstr, "%d", y);
		name = "delimiter_right_";
		name += numstr;

		crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		crate = sceneManager->createEntity(name, "WoodCrate.mesh");
		crateNode->attachObject(crate);
		crateNode->setScale(scaleVector);
		crateNode->setPosition(Ogre::Real(MAP_WIDTH*MAP_TILE_SIZE), 12.5, Ogre::Real(y*MAP_TILE_SIZE));
	}
}

std::string World::getWinnerName()
{
	int winingId = 0;
	int teamAlive = 0;
	for(int i = 0; i < teamCount; ++i)
	{
		if(teams[i]->getCumulativeLife() > 0)
		{
			++teamAlive;
			winingId = teams[i]->getId();
		}
	}

	if(teamAlive < 2 && winingId != 0)
	{
		if(winingId != 0)
		{
			return getTeam(winingId)->getName();
		}
		else
		{
			return "Tie";
		}
	}
	return "";
}

bool World::isGameStarted()
{
	return gameStarted;
}