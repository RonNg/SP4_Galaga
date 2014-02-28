#include "Entities\PowerUps\PowerUp.h"


ippPowerUp::ippPowerUp(void)
{
}

ippPowerUp::ippPowerUp ( float sizeX, float sizeY )
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	direction = Vec3D ( 0.0f, 1.0f, 0.0f );

	this->alive = false;
}

ippPowerUp::~ippPowerUp(void)
{
}

void ippPowerUp::Render ()
{
	if ( alive )
	{
		// Rendering the powerup
		glPushMatrix();

		glTranslatef ( position.x, position.y, 0 );

		glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f );
		glEnable ( GL_BLEND );//Blending for alpha effects
		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, powerUp.texID);

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

void ippPowerUp::Update ()
{
	if ( alive )
	{
		// If the bullet hit near the edge of the screen, derender it
		if ( position.y > Global::HEIGHT_RESOLUTION )
		{
			alive = false;
			powerType = "";
		}

		position += direction * 8 * Global::timedelta;
	}
}

void ippPowerUp::SetAlive ( bool alive )
{
	this->alive = alive;
}

void ippPowerUp::SetType ( string powerType )
{
	this->powerType = powerType;
}