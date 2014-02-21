#include "Ship.h"

#include "Entities\Weapons\TurretClass.h"
#include "Entities\Weapons\MissileLauncher.h"
#include "Entities\QuadClass.h"

#include "Globals.h"
using namespace Global;

ippShip::ippShip(float x, float y, float z)
{
	position.Set ( x, y, z );
	ship = new ippQuadClass ();
	turret = new ippTurretClass ();
	missileLauncher = new ippMissileLauncher ();
}


ippShip::~ippShip(void)
{
	delete ship;
}

void ippShip::Init()
{
	//Sets direction to face upwards
	direction.Set(0, -1, 0); 
	moveSpeed = 10.0f;

	// Sets the number of bullets
	turret->Init ( 30 );
	missileLauncher->Init ( 20 );

	// Ship rendering settings
	ship->SetLW ( 20.0f, 20.0f );
}
void ippShip::Update()
{
	turret->Update ();
	missileLauncher->Update ();
	// Update ship position
	ship->SetXY ( position.x, position.y );
}

void ippShip::Render ()
{
	turret->Render ();
	missileLauncher->Render ();
	// Rendering the ship
	ship->DrawQuads ();
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
	turret->FireWeapon ( position, direction );
}

void ippShip::FireMissile ( Vec3D* tPosition )
{
	missileLauncher->FireMissile ( position, direction, tPosition );
}