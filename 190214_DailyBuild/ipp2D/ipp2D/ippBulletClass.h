#pragma once

#include "ippWeaponClass.h"

class ippBulletClass : public ippWeaponClass
{
public:
	ippBulletClass ( void );
	ippBulletClass ( Vec3D position, Vec3D direction, float speed, int damage, float sizeX, float sizeY );
	~ippBulletClass ( void );

	void Update ( void );
	void Render ( void );
};

