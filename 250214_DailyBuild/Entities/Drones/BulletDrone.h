#pragma once

#include <vector>
#include "Entities\Drones\DroneClass.h"
#include "Entities\Weapons\Bullet.h"


class ippBulletDrone
	:public ippDroneClass
{
public:
	ippBulletDrone(void);
	ippBulletDrone ( Vec3D* position, float sizeX, float sizeY );
	~ippBulletDrone(void);

	void Update ( void );
	void Render ( void );
	void Init ( int numOfBullets, float speed, int damage, float delay );

	std::vector<ippBullet*> bulletList;
	int bulletIndex;

private:
	float delay;
	float curTime;
};

