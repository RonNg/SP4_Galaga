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

	bulletDrone = new ippBulletDrone ( &position, 10.0f, 10.0f );

	ippObjectManager::GetInstance()->AddObj(this);
}

ippShip::~ippShip(void)
{
}

void ippShip::Init()
{
	//Sets direction to face upwards
	direction.Set(0, -1, 0); 
	moveSpeed = 10.0f;
	
	// Sets the number of bullets
	turret->Init ( 30 );
	missileLauncher->Init ( 20 );

	// Adding Drone into the manager
	ippObjectManager::GetInstance ()->AddObj ( bulletDrone );

	// Calling bulletDrone's init to add the bullet into the manager
	bulletDrone->Init ();
}
void ippShip::Update()
{
	/*turret->Update ();
	missileLauncher->Update ();*/
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
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, missile[0].texID);

	glBegin ( GL_QUADS );

		glTexCoord2f(0.0f, 0.0f);	glVertex2f ( -sizeX, sizeY );
		glTexCoord2f(0.0f, 1.0f);	glVertex2f ( -sizeX, -sizeY );
		glTexCoord2f(1.0f, 1.0f);	glVertex2f ( sizeX, -sizeY );
		glTexCoord2f(1.0f, 0.0f);	glVertex2f ( sizeX, sizeY );

	glEnd();

	//glDisable(GL_TEXTURE_2D);
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
	Vec3D offSet ( 0, -10.0f, 0 );
	turret->FireWeapon ( position + offSet, direction );
}

void ippShip::FireMissile ( Vec3D* tPosition )
{
	missileLauncher->FireMissile ( position, direction, tPosition );
}