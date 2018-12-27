#include "ItemSuperPotion.h"



void CItemSuperPotion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CActiveObject::Update(dt);
	vy += GAME_GRAVITY * dt;				// simple fall down

	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);


	// Pick animation
	this->currentAniID = (int)ItemSuperPotionAniID::IDLE;


	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
		CActiveObject::ProceedCollisions(coEvents);


	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	// If the item rope goes out the viewport
	if (this->IsInViewport() == false)
		SetState(STATE_INVISIBLE);
}

void CItemSuperPotion::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + ITEM_SUPER_POTION_BBOX_WIDTH;
	bottom = top + ITEM_SUPER_POTION_BBOX_HEIGHT;
}
