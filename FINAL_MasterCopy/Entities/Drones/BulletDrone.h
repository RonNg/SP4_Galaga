#pragma once

#include <vector>
#include "Entities\Drones\DroneClass.h"
#include "Entities\Weapons\Bullet.h"
#include "LoadTGA\LoadTGA.h"

// Lua scripting
extern "C" {
#include "LUA\lua.h"
#include "LUA\lualib.h"
#include "LUA\lauxlib.h"
}

class ippBulletDrone
	:public ippDroneClass
{
public:
	ippBulletDrone(void);
	ippBulletDrone ( Vec3D* position, float sizeX, float sizeY );
	~ippBulletDrone(void);

	void Update ( void );
	void Render ( void );
	void Init ( int numOfBullets, int rechargeLevel );

	std::vector<ippBullet*> bulletList;
	int bulletIndex;

private:
	float delay;
	float curTime;

	TextureImage drone;
};

