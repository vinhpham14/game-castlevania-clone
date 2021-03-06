#include "algorithm"

#include "MovableObject.h"
#include "Game.h"
#include "ItemRope.h"
#include "InvisibleWall.h"
#include "debug.h"

#include "Simon.h"
#include "Zombie.h"

CActiveObject::CActiveObject()
{
	vx = 0;
	vy = 0;
	nx = 1;
}

void CActiveObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Being Untouchable
	if (untouchable_start != TIMER_IDLE &&
		untouchable_start != TIMER_ETERNAL)
		ProceedBeingUntouchable();

	this->dt = dt;
	this->dx = vx * dt;
	this->dy = vy * dt;
}

/*
	Proceed the collisions with the ground (INVISIBLEWALL) while falling.
	Generically use for simple falling-down objects.
	(Items, Heart,...)
*/
void CActiveObject::ProceedCollisions(vector<LPCOLLISIONEVENT>& coEvents)
{
	vector<LPCOLLISIONEVENT> coEventsResult;
	float min_tx, min_ty, nx, ny;
	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

	// Set the object's position right to the point occured collision
	x += min_tx * dx;
	y += min_ty * dy;

	for (UINT i = 0; i < coEventsResult.size(); ++i)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (dynamic_cast<CInvisibleWall *>(e->obj))
		{
			// Block when reach the ground
			if (e->ny < 0)
			{
				y += DEFLECTION_AVOID_OVERLAPPING * e->ny;
				vy = 0;
			}

			/*if (e->nx != 0)
			{
				x += DEFLECTION_AVOID_OVERLAPPING * e->nx;
				vx = 0;
			}*/
		}	
		else
		{
			// Ignore other objects by completing the rest of dx / dy
			//if (e->nx != 0)	x += (1 - min_tx) * dx;
			//if (e->ny > 0)	y += (1 - min_ty) * dy;
		}
	}
}

void CActiveObject::ProceedBeingUntouchable()
{
	if (GetTickCount() - untouchable_start > UNTOUCHABLE_TIME)
		untouchable_start = TIMER_IDLE;
	else vx = vy = 0;
}

void CActiveObject::BeHit(int damage)
{
	if (untouchable_start == TIMER_IDLE)
	{
		if (health > 0)
			health -= damage;

		// If killed..
		if (health <= 0)
		{
			this->Destroy();
		}

		// If the object is still alive
		else 
			untouchable_start = GetTickCount();
	}
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CActiveObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object if it is: m speed = original m speed - collide object speed
	float svx = 0;
	float svy = 0;
	if (dynamic_cast<CActiveObject *>(coO))
		dynamic_cast<CActiveObject *>(coO)->GetSpeed(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

void CActiveObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty,
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CActiveObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects,
	vector<LPCOLLISIONEVENT> &coEvents)
{
	

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));
		
		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

