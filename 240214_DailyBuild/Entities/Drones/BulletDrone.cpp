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

	delay = 50.0f;
	curTime = 0.0f;
	
	bullet = new ippBullet ( 15.0f, 1, 2.5f, 2.5f );
}

ippBulletDrone::~ippBulletDrone(void)
{
	delete bullet;
}

void ippBulletDrone::Init ( void )
{
	ippObjectManager::GetInstance ()->AddObj ( bullet );
}

void ippBulletDrone::Update ( void )
{
	curTime += Global::timedelta;
	if ( delay < curTime )
	{
		bullet->SetAlive ( true );
		bullet->SetPosition ( Vec3D ( position->x + 50, position->y, position->z ) );
		bullet->SetDirection ( Vec3D ( 0.0f, -1.0f, 0.0f ) );

		curTime = 0.0f;
	}
}

void ippBulletDrone::Render ( void )
{
	// Rendering the drone
	glPushMatrix();

	glTranslatef ( position->x + 50, position->y, 0 );

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