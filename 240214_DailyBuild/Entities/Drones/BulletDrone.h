#pragma once

#include "Entities\Drones\DroneClass.h"
#include "Entities\Weapons\BulletClass.h"


class ippBulletDrone
	:public ippDroneClass
{
public:
	ippBulletDrone(void);
	ippBulletDrone ( Vec3D* position, float sizeX, float sizeY );
	~ippBulletDrone(void);

	void Update ( void );
	void Render ( void );
	void Init ( void );

	ippBulletClass* bullet;

private:
	float delay;
	float curTime;
};

