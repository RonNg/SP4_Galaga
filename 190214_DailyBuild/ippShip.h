#pragma once
#include "Vec3D.h"
#include "GL\freeglut.h"
#include "ippTurretClass.h"
#include "ippMissileLauncher.h"
#include <vector>

#include "ippGlobals.h"
using namespace Global;


class ippShip
{

public:

	ippShip(float x, float y, float z);
	~ippShip(void);

	enum movementCode_t 
	{
		LEFT,
		RIGHT
	};

	virtual void		Init ();
	virtual void		Render ();
	virtual void		Update ();
	virtual void		Movement ( int moveCode );
	void				FireBullet ( void );
	void				FireMissile ( Vec3D* tPosition );
	
	virtual void		SetSpeed ( float moveSpeed ) { this->moveSpeed = moveSpeed; }
	virtual Vec3D		GetPos ( void ) { return position; }

private:
	Vec3D position,		direction;
	ippQuadClass*		ship;
	float				moveSpeed;
	ippTurretClass*		turret;
	ippMissileLauncher*	missileLauncher;
};

