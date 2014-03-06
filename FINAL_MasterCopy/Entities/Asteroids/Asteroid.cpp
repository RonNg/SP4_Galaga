#include "Entities\Asteroids\Asteroid.h"


ippAsteroid::ippAsteroid(void)
{
	sizeX = 10;
	sizeY = 10;
	speed = 10;
	rotVal = 0.0f;
	rotSpeed = 0.0f;

	SetCollider2D ( sizeX + 5, sizeY + 5 );	
	SetTag ( "Asteroid" );
}


ippAsteroid::~ippAsteroid(void)
{
}

void ippAsteroid::SetSize ( float x, float y )
{
	sizeX = x;
	sizeY = y;
}

void ippAsteroid::SetAlive ( bool alive )
{
	this->alive = alive;
}

void ippAsteroid::SetSpeed ( float speed )
{
	this->speed = speed;
}

void ippAsteroid::SetRotSpeed ( float rotSpeed )
{
	this->rotSpeed = rotSpeed;
}

void ippAsteroid::SetPosition ( Vec3D position )
{
	this->position = position;
}

void ippAsteroid::SetDirection ( Vec3D direction )
{
	this->direction = direction;
}

void ippAsteroid::Render ( void )
{
	if ( alive )
	{
		// Rendering the asteroid
		glPushMatrix();

		glTranslatef ( position.x, position.y, 0 );
		glRotatef ( rotVal, 0.0f, 0.0f, 1.0f );

		glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f );
		glEnable ( GL_BLEND );//Blending for alpha effects
		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, asteroid.texID);

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
}

void ippAsteroid::Update ( void )
{
	if ( alive )
	{
		// If the bullet hit near the edge of the screen, derender it
		if ( position.y > Global::HEIGHT_RESOLUTION )
		{
			alive = false;
		}
		position += direction * speed * Global::timedelta;
		rotVal += rotSpeed;
	}
}