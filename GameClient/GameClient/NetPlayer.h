/* ---------------------------------------------------------------------------
**      _____      _____      _____   
**     /     \    /  _  \    /  _  \  
**    /  \ /  \  /  /_\  \  /  /_\  \ 
**   /    Y    \/    |    \/    |    \
**   \____|__  /\____|__  /\____|__  /
**           \/         \/         \/ 
**
** NetController.h
** The network player entity
**
** Author: Moba Action Alpha Team
** -------------------------------------------------------------------------*/

#ifndef __NetPlayer_h_
#define __NetPlayer_h_

#include "stdafx.h"

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

class NetPlayer
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

	std::string tagName;
	std::string meshName;
	int mCurrentSpeed;
	SceneNode* mBodyNode;
	SceneManager* mSceneMgr;
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
	Vector3 targetPosition;
	Real mVerticalVelocity;     // for jumping
	Real mTimer;                // general timer to see how long animations have been playing
	TerrainGroup* mTerrainGroup;

	void setupBody(SceneManager* sceneMgr);
	void setupAnimations();
	void updateBody(Real deltaTime);
	void updateHeight();
	void updateAnimations(Real deltaTime);
	void fadeAnimations(Real deltaTime);
	void setBaseAnimation(AnimID id, bool reset = false);
	void setTopAnimation(AnimID id, bool reset = false);

public:
	NetPlayer(SceneManager* sceneMgr, TerrainGroup* mTerrainGroup, std::string tagName, std::string meshName, Vector3 targetPosition);
	~NetPlayer();
	void addTime(Real deltaTime);
	void updateDestination(Vector3 position);
};

#endif // #ifndef __NetPlayer_h_