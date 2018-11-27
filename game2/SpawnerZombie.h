#pragma once
#include "MovableObject.h"

#define REST_TIME						500			// Rest time before spawn another zombie
#define PAUSE_TIME						5000		// Pause time before another spawn-season starts
#define NUMBER_OF_ZOMBIES				3			// Number of zombies will be spawn in a single spawn-season

/*
	The class describes an invisible object.
	When Simon overlaps on this, Zombie monster will be spawned by somehow.
*/
class CSpawnerZombie: public CActiveObject
{
	float width;
	float height;

	// The number of zombie that has already spawned in the spawn-season
	int spawnCounter;	

	// Timer
	DWORD rest_start;
	DWORD pause_start;

public:

	void GetBoundingBox(float &left, float &top, float &right, float &bottom) override;
	void Render() override { /* Nothing here */ }
	void Update(DWORD dt, vector<LPGAMEOBJECT> * coObjects) override;

	void SetSize(float width, float height);
	void SetupZombieInfo(float &x, float &y, int &nx);
	CSpawnerZombie();
};
