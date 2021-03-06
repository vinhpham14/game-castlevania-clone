#pragma once
#include "MovableObject.h"

#define PANTHER_IDLE_BBOX_HEIGHT	32.0f
#define PANTHER_IDLE_BBOX_WIDTH		48.0f

#define PANTHER_RUN_BBOX_HEIGHT		32.0f
#define PANTHER_RUN_BBOX_WIDTH		64.0f

#define PANTHER_RUN_SPEED			0.25f
#define PANTHER_JUMP_SPEED			0.35f
#define PANTHER_FALL_GRAVITY		0.0012f
#define PANTHER_FIND_RADIUS			112.0f

#define PANTHER_DEFAULT_HEALTH		1
#define PANTHER_DAMAGE				2
#define PANTHER_POINT_AWARD			200


enum class PantherAniID
{
	IDLE_RIGHT = 5200,
	IDLE_LEFT ,	
	RUN_RIGHT,
	RUN_LEFT,
	JUMP_RIGHT,
	JUMP_LEFT,
	
};

class CPanther : public CActiveObject
{
	bool jumping;
	LPGAMEOBJECT groundStandingOn;	// The ground that the panther is standing on

public:

	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Update(DWORD dt, vector<LPGAMEOBJECT> * coObjects) override;
	void SetState(int state) override;

	bool FindSimon(float radius);
	bool CheckIfNeedJump();

	void Jump();
	void ChangeDirectonToSimon();
	void PickAnimation();
	void ProceedCollisions(vector<LPCOLLISIONEVENT> & coEvents);

	CPanther();
};

