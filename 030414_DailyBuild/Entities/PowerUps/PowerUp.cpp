#include "Entities\PowerUps\PowerUp.h"


ippPowerUp::ippPowerUp(void)
{
}

ippPowerUp::ippPowerUp ( float sizeX, float sizeY )
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	position = Vec3D ( Global::WIDTH_RESOLUTION/2, 0.0f, 0.0f );

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

		if ( powerType == "HealthPower" )
		{
			glColor4f ( 1.0f, 0.0f, 0.0f, 1.0f );
		}
		if ( powerType == "MissilePower" )
		{
			glColor4f ( 0.0f, 1.0f, 0.0f, 1.0f );
		}
		if ( powerType == "SpeedPower" )
		{
			glColor4f ( 0.0f, 0.0f, 1.0f, 1.0f );
		}

		glEnable ( GL_BLEND );//Blending for alpha effects
		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, powerUp.texID);

		glBegin ( GL_QUADS );

			glTexCoord2f(0.0f, 0.0f);	glVertex2f ( -( sizeX/2 ), -( sizeY/2 ) );
			glTexCoord2f(0.0f, 1.0f);	glVertex2f ( -( sizeX/2 ), sizeY/2 );
			glTexCoord2f(1.0f, 1.0f);	glVertex2f ( sizeX/2, sizeY/2 );
			glTexCoord2f(1.0f, 0.0f);	glVertex2f ( sizeX/2, -( sizeY/2 ) ); 

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

bool ippPowerUp::OnCollisionEnter ( ippCollider2D* col )
{
	if ( col->GetGameObject()->GetTag() == "Player" )
	{
   		Destroy ( col->GetGameObject() );
		return true;
	}

	return false;
}