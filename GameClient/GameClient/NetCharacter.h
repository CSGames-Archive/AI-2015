/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetCharacter.h
** The Character that is controlled by the AI
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __NetCharacter_h_
#define __NetCharacter_h_

#include "stdafx.h"

#include <iostream>
#include <queue>

#include "NetUtility.h"

using namespace Ogre;

#define NB_ANIMATIONS 5			// number of animations the character has
#define CHARACTER_HEIGHT 5		// height of character's center of mass above ground
#define WALK_SPEED 50			// character walking speed in units per second

class NetCharacter
{
	enum AnimationID
	{
		ANIM_IDLE_BASE,
		ANIM_IDLE_TOP,
		ANIM_RUN_BASE,
		ANIM_RUN_TOP,
		ANIM_DANCE,
		ANIM_NONE
	};

private:
	// Network
	std::queue<std::string>* messageQueue;
	int teamId;
	int characterId;
	Vector3 lastSendPosition;

	// Character Infos
	std::string name;
	Vector3 targetPosition;

	// 3D world components
	std::string meshName;
	SceneNode* bodyNode;
	SceneManager* sceneManager;
	Entity* bodyEntity;

	// Animations
	AnimationState* animations[NB_ANIMATIONS];
	AnimationID baseAnimationID;
	AnimationID topAnimationID;

	void setupBody();
	void updateBody(Real deltaTime);
	void setupAnimations();
	void updateAnimations(Real deltaTime);
	void setBaseAnimation(AnimationID id, bool reset = false);
	void setTopAnimation(AnimationID id, bool reset = false);

public:
	NetCharacter(SceneManager* sceneManager, std::queue<std::string>* messageQueue,
		std::string name, std::string meshName, Vector3 startingPosition, int teamId, int characterId);
	~NetCharacter();
	void addTime(Real deltaTime);
	void setTargetPosition(Vector3 targetPosition);
};

#endif // #ifndef __NetCharacter_h_