#include "Bullet.h"

#include "Components\Colliders\Collider.h"
#include "Managers\ObjectManager.h"
#include "Managers\EmitterManager.h"
#include "Managers\GameManager.h"

#include "Entities\Ship\Ship.h"

#include "Globals.h"
using namespace Global;

ippBullet::ippBullet ( float speed, float sizeX, float sizeY, string tag )
{
	alive = false;
	this->speed = speed;
	//this->damage = damage;
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	SetCollider2D ( sizeX + 5, sizeY + 5 );	
	SetTag ( tag );

	LoadTGA ( &bullet[0], "Images/Weapons/gBullet.tga" );
	ippObjectManager::GetInstance()->AddObj ( this );
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
				position.y < 0 ||
				position.y > Global::HEIGHT_RESOLUTION )
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
	//It can only either be Enemy collide with Player or vice versa, mutually exclusive.
	//Hence two if statements and returning true inside
	if ( col->GetGameObject()->GetTag() == "Enemy" && this->IsAlive() && this->GetTag() != "Enemy Bullet" )
	{
		// Create an explosion at the spot where enemy died.
		ippEmitterManager::GetInstance()->CreateExplosion( col->GetGameObject()->GetPosition() );

		//Plays sound for enemy death
		bool playOnce = true;
		if ( playOnce )
		{
			Sound_EnemyDeath = Global::theSoundEngine->play2D("Sounds/Kill.mp3",false);

			playOnce = false;
		}

		ippGameManager::GetInstance()->highscore += 25;

		
		//Finally, destroys it to free memory
   		Destroy ( col->GetGameObject() );
		SetAlive ( false );
		return true;
	}

	//Player gets hit by Enemy Bullet
	if ( col->GetGameObject()->GetTag() == "Player" && this->GetTag() == "Enemy Bullet"  && this->alive )
	{
		// Create an explosion at the spot where enemy died.
		ippEmitterManager::GetInstance()->CreateExplosion( col->GetGameObject()->GetPosition() );

		ippShip* temp = (ippShip*) col->GetGameObject();

		temp->SetAlive ( false );
		SetAlive ( false );
		return true;
	}

	return false;
}