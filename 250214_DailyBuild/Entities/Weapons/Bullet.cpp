#include "Bullet.h"

#include "Globals.h"
using namespace Global;

ippBullet::ippBullet ( void )
{
	direction = Vec3D ( 0.0f, -1.0f, 0.0f );
}

ippBullet::ippBullet ( float speed, int damage, float sizeX, float sizeY )
{
	alive = false;
	this->speed = speed;
	this->damage = damage;
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	SetCollider2D ( sizeX + 5, sizeY + 5 );	
	SetTag ( "Bullet" );

	LoadTGA ( &bullet[0], "bullet.tga" );
}

ippBullet::~ippBullet ( void )
{
}

void ippBullet::SetAlive ( bool alive )
{
	this->alive = alive;
}

void ippBullet::SetPosition ( Vec3D position )
{
	this->position = position;
}

void ippBullet::SetDirection ( Vec3D direction )
{
	this->direction = direction;
}

void ippBullet::Update ( void )
{
	if ( alive )
		{

			// If the bullet hit near the edge of the screen, derender it
			if ( position.x < 0 ||
				position.x > Global::WIDTH_RESOLUTION ||
				position.y < 0 )
			{
				alive = false;
			}

			position += direction * speed * Global::timedelta;
		}
}

void ippBullet::Render ( void )
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

bool ippBullet::OnCollisionEnter ( ippCollider2D* col )
{
	if ( col->GetGameObject()->GetTag() == "Enemy" )
	{
   		Destroy ( col->GetGameObject() );
		return true;
	}

	return false;
}