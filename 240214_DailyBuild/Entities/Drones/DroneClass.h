#pragma once

#include "Entities\GameObject.h"
#include "Vec3D.h"

class ippDroneClass
	: public ippGameObject
{
public:
	ippDroneClass(void);
	~ippDroneClass(void);

	virtual void	Update ( void ) = 0;
	virtual void	Render ( void ) = 0;
	virtual void	Init ( void ) = 0;

protected:
	Vec3D*			position;
	Vec3D			tPosition;
	float			sizeX;
	float			sizeY;
};

