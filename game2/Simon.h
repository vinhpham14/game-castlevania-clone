#pragma once
#include "MovableObject.h"

#define SIMON_IDLE_BBOX_WIDTH			32
#define SIMON_IDLE_BBOX_HEIGHT			60
#define SIMON_CROUCHING_BBOX_WIDTH		32
#define SIMON_CROUCHING_BBOX_HEIGHT		46

#define SIMON_WALKING_SPEED				0.1f
#define SIMON_JUMP_SPEED_Y				0.41f
#define SIMON_GRAVITY					0.0012f

#define SIMON_STATE_IDLE				0
#define SIMON_STATE_WALK_RIGHT			100
#define SIMON_STATE_WALK_LEFT			101
#define SIMON_STATE_CROUCH				200
#define SIMON_STATE_JUMP				300
#define SIMON_STATE_UPSTAIR				400
#define SIMON_STATE_DOWNSTAIR			410
#define SIMON_STATE_ATTACK				900
#define SIMON_STATE_CROUCH_ATTACK		910
#define SIMON_STATE_UPSTAIR_ATTACK		910
#define SIMON_STATE_DOWNSTAIR_ATTACK	920
#define SIMON_STATE_GO_IN				999
#define SIMON_STATE_DIE					1000

#define ATTACKING_TIME					300

enum SimonAniID
{
	IDLE_RIGHT = 9900,
	IDLE_LEFT,
	WALK_RIGHT,
	WALK_LEFT,
	CROUCH_RIGHT,
	CROUCH_LEFT,
	ATTACK_RIGHT,
	ATTACK_LEFT,
	PUSHED_BACK_RIGHT,
	PUSHED_BACK_LEFT,
	DOWN_STAIR_RIGHT,
	DOWN_STAIR_LEFT,
	UP_STAIR_RIGHT,
	UP_STAIR_LEFT,
	CROUCH_ATTACK_RIGHT,
	CROUCH_ATTACK_LEFT,
	DOWN_STAIR_ATTACK_RIGHT,
	DOWN_STAIR_ATTACK_LEFT,
	UP_STAIR_ATTACK_RIGHT,
	UP_STAIR_ATTACK_LEFT,
	GO_IN
};

class CSimon : public CMovableObject
{
	int attacking;
	int jumping;
	int crouching;
	int stairing;
	DWORD attacking_start_time;

	static unordered_map<int, LPANIMATION> simonAnimations;

public:
	CSimon();
	
	void StartToAttack();

	void SetState(int state) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL) override;
	void Render() override;
	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void AddAnimation(int aniID) override;
};

