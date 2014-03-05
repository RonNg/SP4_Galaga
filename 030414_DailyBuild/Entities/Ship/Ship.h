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
	void				SetSpeedActive ( bool active );		// Sets if the speedpowerup 

	Vec3D				GetPos ( void ) { return position; }
	int					GetEvasion ( void ) { return evasionRate; }

	//bool				OnCollisionEnter ( ippCollider2D* col );	// Calls when the ship is getting hit

private:
	float				moveSpeed;
	ippTurretClass*		turret;
	ippMissileLauncher*	missileLauncher;
	ippBulletDrone*		bulletDrone;

	float				bulletDelay;
	float				missileDelay;
	float				powerupSpeedDelay;

	float				bulletCurTime;
	float				missileCurTime;
	float				powerupSpeedTime;	//Keep track of how much time does the power up left

	// If weapon is ready to be fired
	bool				bulletReady;
	bool				missileReady;

	bool				speedActivated;		// Speed power up activate
	int					speedBonus;			// Bonus speed the power up p[rovides

	float				sizeX;
	float				sizeY;

	// Ship stats
	int					shipCurHealth;
	int					shipMaxHealth;
	int					evasionRate;	// Rate of evasion out of hundred

	TextureImage ship[1];
};

