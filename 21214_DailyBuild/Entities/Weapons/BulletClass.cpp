#include "BulletClass.h"

#include "Globals.h"
using namespace Global;

ippBulletClass::ippBulletClass ( void )
{
	direction = Vec3D ( 0.0f, -1.0f, 0.0f );
	
}

ippBulletClass::ippBulletClass ( float speed, int damage, float sizeX, float sizeY )
{
	alive = false;
	this->speed = speed;
	this->damage = damage;
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	LoadTGA ( &bullet[0], "bullet.tga" );
}

ippBulletClass::~ippBulletClass ( void )
{
}

void ippBulletClass::SetAlive ( bool alive )
{
	this->alive = alive;
}

void ippBulletClass::SetPosition ( Vec3D position )
{
	this->position = position;
}

void ippBulletClass::SetDirection ( Vec3D direction )
{
	this->direction = direction;
}

void ippBulletClass::Update ( void )
{
	if ( alive )
		{

			// If the bullet hit near the edge of the screen, derender it
			if ( position.x < 0 + 100 ||
				position.x > Global::WIDTH_RESOLUTION - 100 ||
				position.y < 0 + 100 /*||
				position.y < Global::HEIGHT_RESOLUTION - 100*/ )
			{
				alive = false;
			}

			else
			{
				position += direction * speed * Global::timedelta;
			}
		}
}

void ippBulletClass::Render ( void )
{
	if ( alive )
	{
		glPushMatrix();

		glTranslatef ( position.x, position.y, 0 );

		glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f );
		glEnable ( GL_BLEND );//Blending for alpha effects
		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, bullet[0].texID);

		glBegin ( GL_QUADS );

			glTexCoord2f(0.0f, 0.0f);	glVertex2f ( 0, 0 );
			glTexCoord2f(0.0f, 1.0f);	glVertex2f ( 0, sizeY );
			glTexCoord2f(1.0f, 1.0f);	glVertex2f ( sizeX, sizeY );
			glTexCoord2f(1.0f, 0.0f);	glVertex2f ( sizeX, 0 );

		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable ( GL_BLEND );
		glPopMatrix ();
	}
}