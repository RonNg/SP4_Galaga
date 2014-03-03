#pragma once
#include "Vec3D.h"
#include "GL\freeglut.h"
#include <vector>
#include "LoadTGA\LoadTGA.h"

// Lua scripting
extern "C" {
#include "LUA\lua.h"
#include "LUA\lualib.h"
#include "LUA\lauxlib.h"
}

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

	virtual void		Init ( int moveSpeedLevel, int evasionRateLevel );
	virtual void		Render ();
	virtual void		Update ();
	virtual void		Movement ( int moveCode );
	void				FireBullet ( void );
	void				FireMissile ( ippGameObject* enemy );
	
	virtual void		SetSpeed ( float moveSpeed ) { this->moveSpeed = moveSpeed; }
	Vec3D				GetPos ( void ) { return position; }
	int					GetEvasion ( void ) { return evasionRate; }

private:
	float				moveSpeed;
	ippTurretClass*		turret;
	ippMissileLauncher*	missileLauncher;
	ippBulletDrone*		bulletDrone;
	int					numOfMissile;

	int					evasionRate;	// Rate of evasion out of hundred

	float				bulletDelay;
	float				missileDelay;

	float				bulletCurTime;
	float				missileCurTime;

	// If weapon is ready to be fired
	bool				bulletReady;
	bool				missileReady;

	float				sizeX;
	float				sizeY;

	int					shipHealth;

	TextureImage ship[1];
};

