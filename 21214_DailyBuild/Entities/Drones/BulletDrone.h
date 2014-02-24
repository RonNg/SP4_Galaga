#pragma once

#include "Entities\Drones\DroneClass.h"
#include "Entities\Weapons\BulletClass.h"


class ippBulletDrone :
	public ippDroneClass
{
public:
	ippBulletDrone(void);
	~ippBulletDrone(void);

	void Update ();
	void Render ();

	ippBulletClass* bullet;

private:
	float delay;
	float curTime;
};

