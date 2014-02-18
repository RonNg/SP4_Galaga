#pragma once

#include "Vec3D.h"
#include "ippQuadClass.h"
#include "ippGlobals.h"

using namespace Global;

class ippWeaponClass
{
public:
	ippWeaponClass ( void );
	~ippWeaponClass ( void );

	virtual void	Update ( void ) = 0;
	virtual void	Render ( void ) = 0;
	virtual void	Init ( void ) = 0;

	int				GetDamage ( void );
	Vec3D			GetPos ( void ) { return position; }

protected:
	float			sizeX;
	float			sizeY;
	Vec3D			position;
	Vec3D			tPosition;
	Vec3D			direction;
	float			speed;
	int				damage;

	ippQuadClass *	projectile;

};

