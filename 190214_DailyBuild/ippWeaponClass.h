#pragma once

#include <vector>
#include "Vec3D.h"

class ippWeaponClass
{
public:
	ippWeaponClass ( void );
	~ippWeaponClass ( void );

	virtual void	FireWeapon ( Vec3D position, Vec3D direction );
	virtual void	FireMissile ( Vec3D position, Vec3D direction, Vec3D* tPosition );

	virtual void	Update ( void ) = 0;
	virtual void	Render ( void ) = 0;

protected:

};

