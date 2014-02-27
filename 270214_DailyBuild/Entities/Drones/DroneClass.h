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
	virtual void	Init ( void );

protected:
	Vec3D*			position;			// Position to track the ship it is attached to
	Vec3D			dronePosition;		// Position of the drone. Offset from the position of the ship
	Vec3D			droneDirFromShip;	// Drone's direction from ship
	float			angle;				// How much is the drone rotated around the ship by
	Vec3D			tPosition;
	float			sizeX;
	float			sizeY;
};

