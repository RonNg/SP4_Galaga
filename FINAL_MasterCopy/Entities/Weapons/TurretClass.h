#pragma once
#include <vector>
#include "Entities\Weapons\WeaponClass.h"

// Lua scripting
extern "C" {
#include "LUA\lua.h"
#include "LUA\lualib.h"
#include "LUA\lauxlib.h"
}

class ippBullet;
class Vec3D;

#include "irrKlang.h"
using namespace irrklang;

class ippTurretClass :
	public ippWeaponClass
{
public:
	ippTurretClass(void);
	~ippTurretClass(void);

	std::vector<ippBullet*> bulletList;
	int bulletIndex;

	void Init ( int numOfBullets, int speedLevel, int shotLevel );
	void FireWeapon ( Vec3D position, Vec3D direction );
private:
	ISound*		Sound_Fire;
	int shotLevel;
};

