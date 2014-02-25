#include "BulletDrone.h"
#include "Managers\ObjectManager.h"


ippBulletDrone::ippBulletDrone(void)
{
}

ippBulletDrone::ippBulletDrone ( Vec3D* position, float sizeX, float sizeY )
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->position = position;
	//dronePosition = Vec3D ( position->x + 30, position->y - 30, position->z );
	droneDirFromShip = Vec3D ( 0.0f, -1.0f, 0.0f );

	angle = 1.0f;

	delay = 50.0f;
	curTime = 0.0f;

	ippObjectManager::GetInstance ()->AddObj ( this );
}

ippBulletDrone::~ippBulletDrone(void)
{
	for ( int i = 0; i < bulletList.size (); i++)
	{
		delete bulletList.at ( i );
	}

	bulletList.clear ();
}

void ippBulletDrone::Init ( int numOfBullets, float speed, int damage, float delay )
{
	for ( int i = 0; i < numOfBullets; i++ )
	{
		bulletList.push_back ( new ippBullet ( 15.0f, 1, 5.0f, 10.0f ) );
		ippObjectManager::GetInstance()->AddObj(bulletList.back());
	}

	this->delay = delay;
}

void ippBulletDrone::Update ( void )
{
	droneDirFromShip.Rotate2D ( angle, true );
	dronePosition = (Vec3D ( position->x + ( droneDirFromShip.x * 20 ), position->y + ( droneDirFromShip.y * 20 ), position->z + ( droneDirFromShip.z * 20 ) ) );

	curTime += Global::timedelta;
	if ( delay < curTime )
	{
		if ( bulletIndex >= bulletList.size() )
		{
			bulletIndex = 0;
		}
		bulletList.at ( bulletIndex )->SetAlive ( true );
		bulletList.at ( bulletIndex )->SetPosition ( Vec3D ( dronePosition.x, dronePosition.y, dronePosition.z ) );
		bulletList.at ( bulletIndex )->SetDirection ( Vec3D ( 0.0f, -1.0f, 0.0f ) );

		curTime = 0.0f;

		++ bulletIndex = 0;
	}
}

void ippBulletDrone::Render ( void )
{
	// Rendering the drone
	glPushMatrix();

	glTranslatef ( dronePosition.x, dronePosition.y, 0 );

	glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable ( GL_BLEND );//Blending for alpha effects
	glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, missile[0].texID);

	glBegin ( GL_QUADS );

		glTexCoord2f(0.0f, 0.0f);	glVertex2f ( -(sizeX/2), -(sizeY/2) );
		glTexCoord2f(0.0f, 1.0f);	glVertex2f ( -(sizeX/2), sizeY/2 );
		glTexCoord2f(1.0f, 1.0f);	glVertex2f ( sizeX/2, sizeY/2 );
		glTexCoord2f(1.0f, 0.0f);	glVertex2f ( sizeX/2, -(sizeY/2) );

	glEnd();

	//glDisable(GL_TEXTURE_2D);
	glDisable ( GL_BLEND );
	glPopMatrix ();
}