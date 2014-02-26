#pragma once
#include "Entities\Weapons\WeaponClass.h"

// Lua scripting
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


class ippMissile;


class ippMissileLauncher :
	public ippWeaponClass
{
public:
	ippMissileLauncher(void);
	~ippMissileLauncher(void);

	std::vector<ippMissile*> missileList;
	int missileIndex;

	void Init ( int numOfMissile, int turnSpeedLevel, int speedLevel, int damageLevel );
	void FireMissile ( Vec3D position, Vec3D direction, Vec3D* tPosition );

	void Update ( void );
	void Render ( void );
};

