#pragma once
#include "Vec3D.h"
#include "GL\freeglut.h"
#include "ippBulletClass.h"
#include <vector>

#include "ippGlobals.h"
using namespace Global;


class ippShip
{

public:

	ippShip(float x, float y, float z);
	~ippShip(void);

	std::vector<ippWeaponClass*> weaponList;

	enum movementCode_t 
	{
		LEFT,
		RIGHT
	};

	virtual void	Init ();
	virtual void	Render ();
	virtual void	Update ();
	virtual void	Movement ( int moveCode );
	virtual void	FireBullet ();
	
	virtual void	SetSpeed ( float moveSpeed ) { this->moveSpeed = moveSpeed; }
	virtual Vec3D	GetPos ( void ) { return position; }

private:
	Vec3D position, direction;
	ippQuadClass*	ship;
	float			moveSpeed;

	
};

