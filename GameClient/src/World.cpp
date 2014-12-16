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

World::World(Ogre::SceneManager* sceneManager, std::queue<std::string>* netMessageQueue)
{
	TANK_MESH_HEIGHT = 2.5;
	TANK_MESH_NAME = "Tank.mesh";

	this->netMessageQueue = netMessageQueue;
	this->sceneManager = sceneManager;
	teamCount = 0;

	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		teams[i] = NULL;
	}
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

void World::createScene()
{
	//TODO: Refactor with the new map
	// Set the scene's ambient light
	sceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	// Create a Light and set its position
	Ogre::Light* light = sceneManager->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);

	Ogre::Light* light2 = sceneManager->createLight("MainLight2");
	light2->setPosition(-20.0f, 80.0f, -50.0f);

	Ogre::Plane plane;
	plane.d = 1000;
	plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	sceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);

	// create a floor mesh resource
	Ogre::MeshManager::getSingleton().createPlane("floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 1000, 1000, 10, 10, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);

	// create a floor entity, give it a material, and place it at the origin
	Ogre::Entity* floor = sceneManager->createEntity("Floor", "floor");
	floor->setMaterialName("SceneMaterial/FloorSand");
	floor->setCastShadows(false);
	sceneManager->getRootSceneNode()->attachObject(floor);

	Ogre::SceneNode* crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* crate = sceneManager->createEntity("crate", "WoodCrate.mesh");
	crateNode->attachObject(crate);
}

void World::addTeam(int teamId, std::string teamName, std::string characterNames[MAX_CHARACTER_PER_TEAM])
{
	Team* team = new Team(teamName, teamId);
	teams[teamCount++] = team;

	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		// TODO: refactor with map infos
		Ogre::Vector3 startingPosition(0, TANK_MESH_HEIGHT ,0);
		Ogre::SceneNode* bodyNode = sceneManager->getRootSceneNode()->createChildSceneNode(startingPosition);
		Ogre::Entity* entity = sceneManager->createEntity(characterNames[i], TANK_MESH_NAME);
		bodyNode->attachObject(entity);

		Character* character = new Character(netMessageQueue, bodyNode, characterNames[i], teamId, i);
		team->addCharacter(character);
	}

	if(teamCount == MAX_TEAM)
	{
		gameStart();
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
			teams[i]->addTime(deltaTime);
		}
	}
}

void World::gameStart()
{
	char numstr[21]; // Enough to hold all numbers up to 64-bits
	sprintf(numstr, "%d", MAX_TEAM);
	std::string message = "Game:GameStart:";
	message += numstr;
	sprintf(numstr, "%d", MAX_CHARACTER_PER_TEAM);
	message += ":";
	message += numstr;

	for(int i = 0; i < MAX_TEAM; ++i)
	{
		sprintf(numstr, "%d", teams[i]->getId());
		message += ":";
		message += numstr;
	}
	netMessageQueue->push(message);
}