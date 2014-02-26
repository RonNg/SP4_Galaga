#include "Ship.h"

#include "Entities\Weapons\TurretClass.h"
#include "Entities\Weapons\MissileLauncher.h"
#include "Entities\QuadClass.h"
#include "Entities\Drones\BulletDrone.h"

#include "Managers\ObjectManager.h"

#include "Globals.h"
using namespace Global;

ippShip::ippShip(float x, float y, float z, float sizeX, float sizeY)
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	position.Set ( x, y, z );
	turret = new ippTurretClass ();
	missileLauncher = new ippMissileLauncher ();
	SetCollider2D(sizeX, sizeY);

	evasionRate = 0;

	bulletDelay = 3.0f;
	missileDelay = 10.0f;

	bulletCurTime = 0.0f;
	missileCurTime = 0.0f;

	ippObjectManager::GetInstance()->AddObj(this);
}

ippShip::~ippShip(void)
{
}

void ippShip::Init( float moveSpeed, int evasionRate )
{
	// Starting lua
	lua_State *L = lua_open();

	// Load the libs
	luaL_openlibs(L);
	// Loading the lua file
	if(luaL_loadfile(L, "config.lua") || lua_pcall(L, 0, 0, 0))
	{
		printf("Error: &s", lua_tostring(L, -1));
	}
	
	lua_getglobal(L, "DRONESIZEX");
	float DRONESIZEX = (float)lua_tonumber(L, -1);

	lua_getglobal(L, "DRONESIZEY");
	float DRONESIZEY = (float)lua_tonumber(L, -1);

	LoadTGA ( &ship[0], "ship.tga" );

	//Sets direction to face upwards
	direction.Set(0, -1, 0); 
	this->moveSpeed = moveSpeed;
	this->evasionRate = evasionRate;
	
	// Sets the number of bullets
	turret->Init ( 6, 5, 3 );
	missileLauncher->Init ( 2, 5, 5, 1 );

	// Calling bulletDrone's init to add the bullet into the manager
	bulletDrone = new ippBulletDrone ( &position, DRONESIZEX, DRONESIZEY );
	bulletDrone->Init ( 10, 1 );

	lua_close(L);
}
void ippShip::Update()
{
	if ( !bulletReady )
	{
		bulletCurTime += Global::timedelta;

		if ( bulletDelay < bulletCurTime )
		{
			bulletCurTime = 0.0f;
			bulletReady = true;
		}
	}

	/*if ( !missileReady )
	{
		missileCurTime += Global::timedelta;

		if ( missileDelay < missileCurTime )
		{
			missileCurTime = 0.0f;
			missileReady = true;
		}
	}*/
}

void ippShip::Render ()
{
	//turret->Render ();
	//missileLauncher->Render ();

	// Rendering the ship
	glPushMatrix();

	glTranslatef ( position.x, position.y, 0 );

	glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable ( GL_BLEND );//Blending for alpha effects
	glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ship[0].texID);

	glBegin ( GL_QUADS );

		glTexCoord2f(0.0f, 0.0f);	glVertex2f ( -sizeX, sizeY );
		glTexCoord2f(0.0f, 1.0f);	glVertex2f ( -sizeX, -sizeY );
		glTexCoord2f(1.0f, 1.0f);	glVertex2f ( sizeX, -sizeY );
		glTexCoord2f(1.0f, 0.0f);	glVertex2f ( sizeX, sizeY );

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable ( GL_BLEND );
	glPopMatrix ();

}

void ippShip::Movement ( int moveCode )
{
	switch ( moveCode )
	{
	case LEFT:

		position.x -= moveSpeed * Global::timedelta;
		break;
	case RIGHT:
		position.x += moveSpeed * Global::timedelta;
		break;

	}
}

void ippShip::FireBullet ( void )
{
	if ( bulletReady )
	{
		Vec3D offSet ( 0, -10.0f, 0 );
		turret->FireWeapon ( position + offSet, direction );
		bulletReady = false;
	}
}

void ippShip::FireMissile ( Vec3D* tPosition )
{
	//if ( missileReady )
	//{
		Vec3D offSet ( 0, -10.0f, 0 );
		missileLauncher->FireMissile ( position + offSet, direction, tPosition );
		//missileReady = false;
	//}
}