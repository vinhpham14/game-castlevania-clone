#include "Animation.h"
#include "Sprites.h"


CAnimation::CAnimation(int defaultTime)
{
	this->defaultTime = defaultTime; frameStartTime = -1; currentFrame = -1;
}

void CAnimation::AddFrame(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) 
		t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		frameStartTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - frameStartTime > t)
		{
			currentFrame++;
			frameStartTime = now;
			if (currentFrame == frames.size()) 
				currentFrame = 0;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}
