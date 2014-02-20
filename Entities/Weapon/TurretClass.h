#pragma once
#include <vector>
#include "Entities\Weapons\WeaponClass.h"

class ippBulletClass;
class Vec3D;

class ippTurretClass :
	public ippWeaponClass
{
public:
	ippTurretClass(void);
	~ippTurretClass(void);

	std::vector<ippBulletClass*> bulletList;
	int bulletIndex;

	void Init ( int numOfBullets );
	void FireWeapon ( Vec3D position, Vec3D direction );

	void Update ( void );
	void Render ( void );
};

