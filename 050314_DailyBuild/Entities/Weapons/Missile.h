#pragma once

#include "LoadTGA\LoadTGA.h"
#include "Vec3D.h"
#include "Waypoint.h"

#include "Entities\GameObject.h"



class ippMissile
	: public ippGameObject
{
public:
	ippMissile ( void );
	ippMissile ( float turnSpeed, float speed, float sizeX, float sizeY );
	~ippMissile ( void );

	void			Update ( void );
	void			Render ( void );
	void			Rotation ( void );
	void			MoveToWayPoint ( float x, float y );

	void			SetAlive ( bool alive );
	void			SetPosition ( Vec3D position );
	void			SetDirection ( Vec3D direction );
	void			SetMissileDir ( Vec3D& mDirection );
	void			LockTarget ( ippGameObject* enemy );		// Lock on to the object
	void			ResetOldPosition ();
	void			ResetRotVal ();

	//int				GetDamage ( void );
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
	ippGameObject *	tempTarget;			// Stores a temp pointer to the target to check if it's null
	Vec3D			mDirection;			// Missile's direction
	float			speed;
	//int				damage;
	bool			alive;

	ippWaypoint *	wayPoint;

	TextureImage missile[1];

	bool OnCollisionEnter ( ippCollider2D* col );
};

