#pragma once
#include <vector>
#include "Entities\Weapons\WeaponClass.h"

class ippBullet;
class Vec3D;

class ippTurretClass :
	public ippWeaponClass
{
public:
	ippTurretClass(void);
	~ippTurretClass(void);

	std::vector<ippBullet*> bulletList;
	int bulletIndex;

	void Init ( int numOfBullets, float speed, int damage );
	void FireWeapon ( Vec3D position, Vec3D direction );

	//void Update ( void );
	//void Render ( void );
};

