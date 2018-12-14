#include "Weapons.h"
#include "debug.h"
#include "Simon.h"

// To adjusting the Dagger position for similar to origin game
#define Y_DISTANCE_DAGGER_LOWER_SIMON			4.0f

CWeapons * CWeapons::__instance = NULL;

void CWeapons::UseWeapon(Weapon weaponName, LPGAMEOBJECT obj)
{
	float left, top, right, bottom;
	LPGAMEOBJECT weapon = GetWeapon(weaponName);

	if (weapon == NULL)
	{
		DebugOut(L"\n[ERROR] Failed to get weapon (Weapon enum: %d)", weaponName);
		return;
	}

	switch (weaponName)
	{
	case Weapon::DAGGER:
		// Only simon can use this dagger weapon.
		if (dynamic_cast<CSimon *>(obj))
		{
			CSimon * simon = dynamic_cast<CSimon *>(obj);

			// Get the direction depending on Simon's direction
			weapon->SetDirection(simon->GetDirection());
			obj->GetBoundingBox(left, top, right, bottom);

			// Set the weapon position depending on Simon's position
			if (weapon->GetDirection() > 0)
				weapon->SetPosition(right, 
					top + Y_DISTANCE_DAGGER_LOWER_SIMON);
			else
				weapon->SetPosition(left - DAGGER_BBOX_WIDTH, 
					top + Y_DISTANCE_DAGGER_LOWER_SIMON);

			// Set the weapon visible
			weapon->SetState(STATE_VISIBLE);
		}
	default:
		break;
	}
}

LPGAMEOBJECT CWeapons::GetWeapon(Weapon weaponName)
{
	vector<LPGAMEOBJECT> weaponsByName = weapons[weaponName];
	int * quantity = &stock[weaponName];

	// Check if any weapon is available
	if (*quantity > 0)
	{
		for (auto it = weaponsByName.begin(); it != weaponsByName.end(); ++it)
		{
			if ((*it)->GetState() == STATE_INVISIBLE)
			{
				(*quantity)--;
				return *it;
			}
		}
	}
	else
		DebugOut(L"\n[INFO] Out of stock of the weapon (Weapon enum: %d)", (int)weaponName);
	
	return NULL;
}

void CWeapons::Add(Weapon weaponName, LPGAMEOBJECT weapon)
{
	weapon->SetState(STATE_INVISIBLE);
	weapons[weaponName].push_back(weapon);
	stock[weaponName];
}

void CWeapons::AddToStock(Weapon weaponName)
{
	stock[weaponName]++;
}

CWeapons * CWeapons::GetInstance()
{
	if (__instance == NULL)
		__instance = new CWeapons();

	return __instance;
}
