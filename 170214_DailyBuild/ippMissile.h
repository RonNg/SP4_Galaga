#pragma once
#include "ippweaponclass.h"
class ippMissile : public ippWeaponClass
{
public:
	ippMissile ( void );
	ippMissile ( Vec3D position, Vec3D direction, float speed, int damage, float sizeX, float sizeY );
	~ippMissile ( void );

	void Update ( void );
	void Render ( void );
};

