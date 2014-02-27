#pragma once
#include "Vec3D.h"
#include "GL\freeglut.h"
#include <vector>
#include "LoadTGA\LoadTGA.h"

#include "Entities\GameObject.h"
class ippTurretClass;
class ippMissileLauncher;
class ippQuadClass;
class ippBulletDrone;

class ippShip
	: public ippGameObject
{

public:

	ippShip(float x, float y, float z, float sizeX, float sizeY);
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
	float				moveSpeed;
	ippTurretClass*		turret;
	ippMissileLauncher*	missileLauncher;
	ippBulletDrone*		bulletDrone;

	float				bulletDelay;
	float				missileDelay;

	float				bulletCurTime;
	float				missileCurTime;

	// If weapon is ready to be fired
	bool				bulletReady;
	bool				missileReady;

	float				sizeX;
	float				sizeY;

	TextureImage ship[1];
};
