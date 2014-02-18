#pragma once

#include "Vec3D.h"
#include "ippQuadClass.h"
#include "ippWaypoint.h"
#include "ippGlobals.h"

using namespace Global;

class ippMissile
{
public:
	ippMissile ( void );
	ippMissile ( Vec3D position, Vec3D* tPosition, Vec3D direction,float speed, int damage, float sizeX, float sizeY );
	~ippMissile ( void );

	void			Update ( void );
	void			Render ( void );
	void			Rotation ( void );
	void			MoveToWayPoint ( float x, float y );

	int				GetDamage ( void );
	Vec3D			GetPos ( void ) { return position; }

private:
	// Missile rotation variables
	bool			stopRotation;
	float			turnSpeed;
	float			rotVal;
	Vec3D			oldDirection;
	Vec3D			oldTargetPosition;

	float			sizeX;
	float			sizeY;
	Vec3D			position;
	Vec3D *			tPosition;
	Vec3D			direction;
	float			speed;
	int				damage;

	ippQuadClass *	projectile;
	ippWaypoint *	wayPoint;
};

