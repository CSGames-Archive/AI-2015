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

#include "stdafx.h"

#include "NetCharacter.h"

//TODO: verrrry hugly
NetCharacter::NetCharacter(SceneManager* sceneManager, std::queue<std::string>* messageQueue,
	std::string name, std::string meshName, Vector3 startingPosition, int teamId, int characterId)
{
	// Network
	this->messageQueue = messageQueue;
	this->teamId = teamId;
	this->characterId = characterId;
	this->lastSendPosition = startingPosition;

	// Character Infos
	this->name = name;
	this->targetPosition = startingPosition;

	// 3D world components
	this->meshName = meshName;
	this->sceneManager = sceneManager;
	setupBody();

	// Animations
	setupAnimations();
}

NetCharacter::~NetCharacter()
{
}

void NetCharacter::addTime(Real deltaTime)
{
	updateBody(deltaTime);
	updateAnimations(deltaTime);
}

void NetCharacter::setTargetPosition(Vector3 targetPosition)
{
	this->targetPosition = targetPosition;
}

void NetCharacter::setupBody()
{
	bodyNode = sceneManager->getRootSceneNode()->createChildSceneNode(targetPosition);
	//TODO: fix multiple same name bug
	bodyEntity = sceneManager->createEntity(name, meshName);
	bodyNode->attachObject(bodyEntity);
}

void NetCharacter::setupAnimations()
{
	// To blend between animation
	bodyEntity->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	String animationNames[] =
	{"IdleBase", "IdleTop", "RunBase", "RunTop", "Dance"};

	// Load all animations
	for (int i=0; i<NB_ANIMATIONS; i++)
	{
		animations[i] = bodyEntity->getAnimationState(animationNames[i]);
		animations[i]->setLoop(true);
	}

	setBaseAnimation(ANIM_IDLE_BASE);
	setTopAnimation(ANIM_IDLE_TOP);
}

void NetCharacter::updateBody(Real deltaTime)
{
	if(bodyNode != NULL)
	{
		Vector3 currentPosition = bodyNode->getPosition();
		Vector3 currentDirection = targetPosition - currentPosition;

		if(currentDirection.length() > Ogre::Real(5.0))
		{
			currentDirection.normalise();
		}
		else
		{
			currentDirection = Vector3::ZERO;
		}

		if (currentDirection != Vector3::ZERO && baseAnimationID != ANIM_DANCE)
		{
			if (baseAnimationID == ANIM_IDLE_BASE)
			{
				// Start running
				setBaseAnimation(ANIM_RUN_BASE, true);
				if (topAnimationID == ANIM_IDLE_TOP) 
					setTopAnimation(ANIM_RUN_TOP, true);
			}

			bodyNode->setDirection(currentDirection);
			bodyNode->translate(0, 0, deltaTime * WALK_SPEED * animations[baseAnimationID]->getWeight(),
				Node::TS_LOCAL);
		}
		else if (baseAnimationID == ANIM_RUN_BASE)
		{
			// Stop running
			setBaseAnimation(ANIM_IDLE_BASE);
			if (topAnimationID == ANIM_RUN_TOP) setTopAnimation(ANIM_IDLE_TOP);
		}

		Vector3 networkDivergence = lastSendPosition - currentPosition;
		if(networkDivergence.length() > 50)
		{
			messageQueue->push(NetUtility::generateMoveCharacterPacket(teamId, characterId, currentPosition.x, currentPosition.z));
			lastSendPosition = currentPosition;
		}
	}
}

void NetCharacter::updateAnimations(Real deltaTime)
{
	if (baseAnimationID != ANIM_NONE)
		animations[baseAnimationID]->addTime(deltaTime);

	if (topAnimationID != ANIM_NONE)
		animations[topAnimationID]->addTime(deltaTime);
}

void NetCharacter::setBaseAnimation(AnimationID id, bool reset)
{
	baseAnimationID = id;

	if (id != ANIM_NONE)
	{
		animations[id]->setEnabled(true);
		animations[id]->setWeight(0);
		if (reset)
			animations[id]->setTimePosition(0);
	}
}

void NetCharacter::setTopAnimation(AnimationID id, bool reset)
{
	topAnimationID = id;

	if (id != ANIM_NONE)
	{
		animations[id]->setEnabled(true);
		animations[id]->setWeight(0);
		if (reset)
			animations[id]->setTimePosition(0);
	}
}