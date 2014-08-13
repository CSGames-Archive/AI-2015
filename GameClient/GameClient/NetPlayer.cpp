/* ---------------------------------------------------------------------------
**      _____      _____      _____   
**     /     \    /  _  \    /  _  \  
**    /  \ /  \  /  /_\  \  /  /_\  \ 
**   /    Y    \/    |    \/    |    \
**   \____|__  /\____|__  /\____|__  /
**           \/         \/         \/ 
**
** NetPlayer.cpp
** Controller that manage all the network information
**
** Author: Moba Action Alpha Team
** -------------------------------------------------------------------------*/

#include "stdafx.h"
#include "NetPlayer.h"

NetPlayer::NetPlayer(SceneManager* sceneMgr, TerrainGroup* mTerrainGroup, std::string tagName, std::string meshName, Vector3 targetPosition)
{
	this->targetPosition = targetPosition;
	this->tagName = tagName;
	this->meshName = meshName;
	mCurrentSpeed = WALK_SPEED;
	this->mSceneMgr = sceneMgr;

	this->mTerrainGroup = mTerrainGroup;
	setupBody(sceneMgr);
	setupAnimations();
	updateHeight();

	mKeyDirection.z = -1;
	setBaseAnimation(ANIM_RUN_BASE, true);
	setTopAnimation(ANIM_RUN_TOP, true);
}

NetPlayer::~NetPlayer()
{
	delete mBodyNode;
}

void NetPlayer::addTime(Real deltaTime)
{
	updateBody(deltaTime);
	updateAnimations(deltaTime);
}


void NetPlayer::updateDestination(Vector3 position)
{
	targetPosition = position;
}

void NetPlayer::setupBody(SceneManager* sceneMgr)
{
	// create main model
	mBodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(targetPosition/*Vector3::UNIT_Y * CHAR_HEIGHT*/);
	mBodyEnt = sceneMgr->createEntity(tagName, meshName);
	mBodyNode->attachObject(mBodyEnt);
	mKeyDirection = Vector3::ZERO;
	mVerticalVelocity = 0;
}

void NetPlayer::setupAnimations()
{
	// this is very important due to the nature of the exported animations
	mBodyEnt->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	String animNames[] =
	{"IdleBase", "IdleTop", "RunBase", "RunTop", "HandsClosed", "HandsRelaxed", "DrawSwords",
	"SliceVertical", "SliceHorizontal", "Dance", "JumpStart", "JumpLoop", "JumpEnd"};

	// populate our animation list
	for (int i = 0; i < NUM_ANIMS; i++)
	{
		mAnims[i] = mBodyEnt->getAnimationState(animNames[i]);
		mAnims[i]->setLoop(true);
		mFadingIn[i] = false;
		mFadingOut[i] = false;
	}

	// start off in the idle state (top and bottom together)
	setBaseAnimation(ANIM_IDLE_BASE);
	setTopAnimation(ANIM_IDLE_TOP);

	// relax the hands since we're not holding anything
	mAnims[ANIM_HANDS_RELAXED]->setEnabled(true);

}

void NetPlayer::updateBody(Real deltaTime)
{
	if(mBodyNode != NULL)
	{
		Vector3 currentPosition = mBodyNode->getPosition();
		targetPosition.y = currentPosition.y; //We don't care about the y axis
		mGoalDirection = targetPosition - currentPosition;

		if(mGoalDirection.length() < Ogre::Real(5.0))
		{
			mKeyDirection = Vector3::ZERO;
		}
		else
		{
			mGoalDirection.normalise();
			mKeyDirection = mKeyDirection.z = -1;
		}

		if (mKeyDirection != Vector3::ZERO && mBaseAnimID != ANIM_DANCE)
		{
			if (mBaseAnimID == ANIM_IDLE_BASE)
			{
				// start running if not already moving and the player wants to move
				setBaseAnimation(ANIM_RUN_BASE, true);
				if (mTopAnimID == ANIM_IDLE_TOP) setTopAnimation(ANIM_RUN_TOP, true);
			}

			// calculate actually goal direction in world based on player's key directions
			Quaternion toGoal = mBodyNode->getOrientation().zAxis().getRotationTo(mGoalDirection);

			// calculate how much the character has to turn to face goal direction
			Real yawToGoal = toGoal.getYaw().valueDegrees();
			// this is how much the character CAN turn this frame
			Real yawAtSpeed = yawToGoal / Math::Abs(yawToGoal) * deltaTime * TURN_SPEED;
			// reduce "turnability" if we're in midair
			if (mBaseAnimID == ANIM_JUMP_LOOP) yawAtSpeed *= 0.2f;

			// turn as much as we can, but not more than we need to
			if (yawToGoal < 0) yawToGoal = std::min<Real>(0, std::max<Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, yawAtSpeed, 0);
			else if (yawToGoal > 0) yawToGoal = std::max<Real>(0, std::min<Real>(yawToGoal, yawAtSpeed)); //yawToGoal = Math::Clamp<Real>(yawToGoal, 0, yawAtSpeed);

			mBodyNode->yaw(Degree(yawToGoal));

			// move in current body direction (not the goal direction)
			mBodyNode->translate(0, 0, deltaTime * mCurrentSpeed * mAnims[mBaseAnimID]->getWeight(),
				Node::TS_LOCAL);

			updateHeight();
		}
		else if (mBaseAnimID == ANIM_RUN_BASE)
		{
			// stop running if already moving and the player doesn't want to move
			setBaseAnimation(ANIM_IDLE_BASE);
			if (mTopAnimID == ANIM_RUN_TOP) setTopAnimation(ANIM_IDLE_TOP);
		}

		if (mBaseAnimID == ANIM_JUMP_LOOP)
		{
			// if we're jumping, add a vertical offset too, and apply gravity
			mBodyNode->translate(0, mVerticalVelocity * deltaTime, 0, Node::TS_LOCAL);
			mVerticalVelocity -= GRAVITY * deltaTime;

			Vector3 pos = mBodyNode->getPosition();
			if (pos.y <= CHAR_HEIGHT)
			{
				// if we've hit the ground, change to landing state
				pos.y = CHAR_HEIGHT;
				mBodyNode->setPosition(pos);
				setBaseAnimation(ANIM_JUMP_END, true);
				mTimer = 0;
			}
		}
	}
	else
	{
	
	}
}

void NetPlayer::updateHeight()
{
	Vector3 pos = mBodyNode->getPosition();
	pos.y = mTerrainGroup->getHeightAtWorldPosition(pos,0) + CHAR_HEIGHT;
	mBodyNode->setPosition(pos);
}

void NetPlayer::updateAnimations(Real deltaTime)
{
	Real baseAnimSpeed = 1;
	Real topAnimSpeed = 1;

	mTimer += deltaTime;



	// increment the current base and top animation times
	if (mBaseAnimID != ANIM_NONE) mAnims[mBaseAnimID]->addTime(deltaTime * baseAnimSpeed);
	if (mTopAnimID != ANIM_NONE) mAnims[mTopAnimID]->addTime(deltaTime * topAnimSpeed);

	// apply smooth transitioning between our animations
	fadeAnimations(deltaTime);
}

void NetPlayer::fadeAnimations(Real deltaTime)
{
	for (int i = 0; i < NUM_ANIMS; i++)
	{
		if (mFadingIn[i])
		{
			// slowly fade this animation in until it has full weight
			Real newWeight = mAnims[i]->getWeight() + deltaTime * ANIM_FADE_SPEED;
			mAnims[i]->setWeight(Math::Clamp<Real>(newWeight, 0, 1));
			if (newWeight >= 1) mFadingIn[i] = false;
		}
		else if (mFadingOut[i])
		{
			// slowly fade this animation out until it has no weight, and then disable it
			Real newWeight = mAnims[i]->getWeight() - deltaTime * ANIM_FADE_SPEED;
			mAnims[i]->setWeight(Math::Clamp<Real>(newWeight, 0, 1));
			if (newWeight <= 0)
			{
				mAnims[i]->setEnabled(false);
				mFadingOut[i] = false;
			}
		}
	}
}

void NetPlayer::setBaseAnimation(AnimID id, bool reset)
{
	if (mBaseAnimID >= 0 && mBaseAnimID < NUM_ANIMS)
	{
		// if we have an old animation, fade it out
		mFadingIn[mBaseAnimID] = false;
		mFadingOut[mBaseAnimID] = true;
	}

	mBaseAnimID = id;

	if (id != ANIM_NONE)
	{
		// if we have a new animation, enable it and fade it in
		mAnims[id]->setEnabled(true);
		mAnims[id]->setWeight(0);
		mFadingOut[id] = false;
		mFadingIn[id] = true;
		if (reset) mAnims[id]->setTimePosition(0);
	}
}

void NetPlayer::setTopAnimation(AnimID id, bool reset)
{
	if (mTopAnimID >= 0 && mTopAnimID < NUM_ANIMS)
	{
		// if we have an old animation, fade it out
		mFadingIn[mTopAnimID] = false;
		mFadingOut[mTopAnimID] = true;
	}

	mTopAnimID = id;

	if (id != ANIM_NONE)
	{
		// if we have a new animation, enable it and fade it in
		mAnims[id]->setEnabled(true);
		mAnims[id]->setWeight(0);
		mFadingOut[id] = false;
		mFadingIn[id] = true;
		if (reset) mAnims[id]->setTimePosition(0);
	}
}