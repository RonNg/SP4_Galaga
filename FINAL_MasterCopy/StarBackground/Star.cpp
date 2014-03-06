#include "StarBackground\Star.h"


ippStar::ippStar(void)
{
	sizeX = 10;
	sizeY = 10;
	speed = 10;

	LoadTGA ( &star, "Images/Background/star.tga" );

	direction = Vec3D ( 0.0f, 1.0f, 0.0f );
}


ippStar::~ippStar(void)
{
}

void ippStar::SetSize ( float x, float y )
{
	sizeX = x;
	sizeY = y;
}

void ippStar::SetAlive ( bool alive )
{
	this->alive = alive;
}

void ippStar::SetSpeed ( float speed )
{
	this->speed = speed;
}

void ippStar::SetRotSpeed ( float rotSpeed )
{
	this->rotSpeed = rotSpeed;
}

void ippStar::SetPosition ( Vec3D position )
{
	this->position = position;
}

void ippStar::SetDirection ( Vec3D direction )
{
	this->direction = direction;
}

void ippStar::Render ( void )
{
	if ( alive )
	{
		// Rendering the Star
		glPushMatrix();

		glTranslatef ( position.x, position.y, 0 );

		glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f );
		glEnable ( GL_BLEND );//Blending for alpha effects
		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, star.texID);

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

void ippStar::Update ( void )
{
	if ( alive )
	{
		// If the bullet hit near the edge of the screen, derender it

		if ( position.y > Global::HEIGHT_RESOLUTION )
		{

			position.y = -10.0f;
		}
		position += direction * speed * Global::timedelta;
	}
}