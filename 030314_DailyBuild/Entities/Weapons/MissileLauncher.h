#pragma once
#include "Entities\Weapons\WeaponClass.h"

// Lua scripting
extern "C" {
#include "LUA\lua.h"
#include "LUA\lualib.h"
#include "LUA\lauxlib.h"
}


class ippMissile;
class ippGameObject;


class ippMissileLauncher :
	public ippWeaponClass
{
public:
	ippMissileLauncher(void);
	~ippMissileLauncher(void);

	std::vector<ippMissile*> missileList;
	int missileIndex;

	void Init ( int numOfMissile, int turnSpeedLevel, int speedLevel );
	void FireMissile ( Vec3D position, Vec3D direction, ippGameObject* enemy );

	void Update ( void );
	void Render ( void );
};

