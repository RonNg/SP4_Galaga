#include "Entities\PowerUps\PowerUp.h"


#include "Components\Colliders\Collider.h"

ippPowerUp::ippPowerUp(void)
{
}

ippPowerUp::ippPowerUp ( float sizeX, float sizeY )
{
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	textureIndex = 0;

	position = Vec3D ( Global::WIDTH_RESOLUTION/2, 0.0f, 0.0f );

	direction = Vec3D ( 0.0f, 1.0f, 0.0f );

	this->alive = false;

	LoadTGA ( &powerUp[0], "Images/Powerups/missilepower.tga" );
	LoadTGA ( &powerUp[1], "Images/Powerups/speedpower.tga" );

	SetCollider2D ( sizeX + 5, sizeY + 5 );	
	SetTag ( "Powerup" );
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

		if ( powerType == "MissilePower" )
		{
			textureIndex = 0;
		}
		if ( powerType == "SpeedPower" )
		{
			textureIndex = 1;
		}

		glEnable ( GL_BLEND );//Blending for alpha effects
		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, powerUp[textureIndex].texID);

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

void ippPowerUp::SetPosition ( Vec3D position )
{
	this->position = position;
}