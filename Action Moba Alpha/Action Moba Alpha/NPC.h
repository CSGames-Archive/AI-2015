#ifndef __NPC_H__
#define __NPC_H__

#include "stdafx.h"
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

using namespace Ogre;

#define NUM_ANIMS 13           // number of animations the character has
#define CHAR_HEIGHT 5          // height of character's center of mass above ground
#define WALK_SPEED 50          // character walking speed in units per second
#define RUN_SPEED 100          // character running speed in units per second
#define TURN_SPEED 500.0f      // character turning in degrees per second
#define ANIM_FADE_SPEED 7.5f   // animation crossfade speed in % of full weight per second
#define JUMP_ACCEL 30.0f       // character jump acceleration in upward units per squared second
#define GRAVITY 90.0f          // gravity in downward units per squared second

class NPCController
{
private:

	// all the animations our character has, and a null ID
	// some of these affect separate body parts and will be blended together
	enum AnimID
	{
		ANIM_IDLE_BASE,
		ANIM_IDLE_TOP,
		ANIM_RUN_BASE,
		ANIM_RUN_TOP,
		ANIM_HANDS_CLOSED,
		ANIM_HANDS_RELAXED,
		ANIM_DRAW_SWORDS,
		ANIM_SLICE_VERTICAL,
		ANIM_SLICE_HORIZONTAL,
		ANIM_DANCE,
		ANIM_JUMP_START,
		ANIM_JUMP_LOOP,
		ANIM_JUMP_END,
		ANIM_NONE
	};

public:
	
	NPCController(SceneManager* sceneMgr, TerrainGroup* mTerrainGroup)
	{
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

	void addTime(Real deltaTime)
	{
		stalkIt();
		updateBody(deltaTime);
		updateAnimations(deltaTime);
	}

	
private:
	void stalkIt()
	{
		Vector3 allo;
		allo = mSceneMgr->getEntity("SinbadBody")->getParentNode()->getPosition();
	}
	
	void setupBody(SceneManager* sceneMgr)
	{
		// create main model
		mBodyNode = sceneMgr->getRootSceneNode()->createChildSceneNode(/*Vector3::UNIT_Y * CHAR_HEIGHT*/);
		mBodyEnt = sceneMgr->createEntity("NPCBody", "Sinbad.mesh");
		mBodyNode->attachObject(mBodyEnt);
		mKeyDirection = Vector3::ZERO;
		mVerticalVelocity = 0;
	}

	void setupAnimations()
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

	void updateBody(Real deltaTime)
	{
		mGoalDirection = Vector3::ZERO;   // we will calculate this

		if (mKeyDirection != Vector3::ZERO && mBaseAnimID != ANIM_DANCE)
		{
			// calculate actually goal direction in world based on player's key directions
			
			
			mGoalDirection.y = 0;
			mGoalDirection.normalise();

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

	void updateHeight()
	{
		Vector3 pos = mBodyNode->getPosition();
		pos.y = mTerrainGroup->getHeightAtWorldPosition(pos,0) + CHAR_HEIGHT;
		mBodyNode->setPosition(pos);
	}

	void updateAnimations(Real deltaTime)
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

	void fadeAnimations(Real deltaTime)
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

	void setBaseAnimation(AnimID id, bool reset = false)
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

	void setTopAnimation(AnimID id, bool reset = false)
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

	int mCurrentSpeed;
	SceneNode* mBodyNode;
	Real mPivotPitch;
	Entity* mBodyEnt;
	Entity* mSword1;
	Entity* mSword2;
	RibbonTrail* mSwordTrail;
	AnimationState* mAnims[NUM_ANIMS];    // master animation list
	AnimID mBaseAnimID;                   // current base (full- or lower-body) animation
	AnimID mTopAnimID;                    // current top (upper-body) animation
	bool mFadingIn[NUM_ANIMS];            // which animations are fading in
	bool mFadingOut[NUM_ANIMS];           // which animations are fading out
	bool mSwordsDrawn;
	Vector3 mKeyDirection;      // player's local intended direction based on WASD keys
	Vector3 mGoalDirection;     // actual intended direction in world-space
	Real mVerticalVelocity;     // for jumping
	Real mTimer;                // general timer to see how long animations have been playing
	TerrainGroup* mTerrainGroup;
	SceneManager* mSceneMgr;
};


#endif
