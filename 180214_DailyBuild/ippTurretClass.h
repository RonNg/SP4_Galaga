#pragma once

#include "ippWeaponClass.h"
#include "ippBulletClass.h"

class ippTurretClass :
	public ippWeaponClass
{
public:
	ippTurretClass(void);
	~ippTurretClass(void);

	std::vector<ippBulletClass*> bulletList;

	void FireWeapon ( Vec3D position, Vec3D direction );
	

	void Update ( void );
	void Render ( void );
};

