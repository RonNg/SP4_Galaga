#pragma once

#include "Vec3D.h"
#include "Entities\QuadClass.h"
#include "Waypoint.h"
#include "Globals.h"
#include "Entities\GameObject.h"

using namespace Global;

class ippMissile
	: public ippGameObject
{
public:
	ippMissile ( void );
	ippMissile ( float speed, int damage, float sizeX, float sizeY );
	~ippMissile ( void );

	void			Update ( void );
	void			Render ( void );
	void			Rotation ( void );
	void			MoveToWayPoint ( float x, float y );

	void			SetAlive ( bool alive );
	void			SetPosition ( Vec3D position );
	void			SetDirection ( Vec3D direction );
	void			SetTPosition ( Vec3D* tPosition );
	void			ResetOldPosition ();
	void			ResetRotVal ();

	int				GetDamage ( void );
	Vec3D			GetPos ( void ) { return position; }
	bool			IsAlive ( void ) { return alive; }

private:
	// Missile rotation variables
	bool			stopRotation;
	float			turnSpeed;
	float			rotVal;
	Vec3D			oldDirection;
	Vec3D			oldTargetPosition;
	float			sizeX;
	float			sizeY;
	Vec3D *			tPosition;
	float			speed;
	int				damage;
	bool			alive;

	//ippQuadClass *	projectile;
	ippWaypoint *	wayPoint;
};

