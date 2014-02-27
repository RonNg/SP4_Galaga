#include "Missile.h"


ippMissile::ippMissile(void)
{
}

ippMissile::ippMissile (  float turnSpeed, float speed, float sizeX, float sizeY )
	:stopRotation ( false )
	,rotVal ( 0.0f )
	,tPosition ( NULL )
{
	alive = false;
	this->position = position;
	this->tPosition = tPosition;
	this->direction = direction;
	this->turnSpeed = turnSpeed;
	this->speed = speed;
	//this->damage = damage;
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	//projectile = new ippQuadClass ();
	wayPoint = new ippWaypoint ();

	LoadTGA ( &missile[0], "missile.tga" );
}

ippMissile::~ippMissile(void)
{
}

void ippMissile::SetAlive ( bool alive )
{
	this->alive = alive;
}

void ippMissile::SetPosition ( Vec3D position )
{
	this->position = position;
}

void ippMissile::SetDirection ( Vec3D direction )
{
	this->direction = direction;
}

void ippMissile::SetMissileDir ( Vec3D& mDirection )
{
	rotVal = direction.AngleBetweenTwoVector ( mDirection );

	if ( mDirection.x < 0 )
	{
		rotVal = 360 - rotVal;
	}
	
	this->mDirection = mDirection;
}

void ippMissile::SetTPosition ( Vec3D* tPosition )
{
	this->tPosition = tPosition;
}

void ippMissile::ResetOldPosition ()
{
	this->oldTargetPosition = Vec3D ( 0.0f, 0.0f, 0.0f );
}

void ippMissile::ResetRotVal ()
{
	this->rotVal = 0.0f;
}

void ippMissile::Update ( void )
{
	if ( this->IsAlive() )
	{
		if ( oldTargetPosition != Vec3D ( tPosition->x, tPosition->y, tPosition->z ) )
		{
			oldTargetPosition = Vec3D ( tPosition->x, tPosition->y, tPosition->z );
			MoveToWayPoint(tPosition->x, tPosition->y);	
		}

		Rotation ();
		
		// If the bullet hit near the edge of the screen, derender it
		if ( position.x < 0 ||
			position.x > Global::WIDTH_RESOLUTION ||
			position.y < 0 )
		{
			alive = false;
		}

		// Movement of the missile
		position += mDirection * speed * Global::timedelta;
	}
}

void ippMissile::Render ( void )
{
	if ( this->IsAlive() )
	{
		glPushMatrix();

		glTranslatef ( position.x, position.y, 0 );
		glRotatef ( rotVal, 0.0f, 0.0f, 1.0f );

		glColor4f ( 1.0f, 1.0f, 1.0f, 1.0f );
		glEnable ( GL_BLEND );//Blending for alpha effects
		glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, missile[0].texID);

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

void ippMissile::Rotation()
{
	Vec3D targetDir = wayPoint->position - position;
	Vec3D result = targetDir.crossVec3D(mDirection);
	result.Normalize();
	targetDir.Normalize();

	if ( !stopRotation )
	{
		if (result.z < 0)
		{
			//cw
			rotVal += turnSpeed;
			mDirection.Rotate2D(turnSpeed, true);
			Vec3D newResult = targetDir.crossVec3D(mDirection);
			if ( newResult.z > 0 )
			{
				//Code must be present, prevents direction from misaligning
				oldDirection = mDirection;
				mDirection = targetDir;

				rotVal -= oldDirection.AngleBetweenTwoVector(mDirection);
				stopRotation = true;
			}
		}
		else if ( result.z > 0)
		{
			rotVal -= turnSpeed;
			mDirection.Rotate2D(-turnSpeed, true);
			Vec3D newResult = targetDir.crossVec3D(mDirection);
			if ( newResult.z < 0 )
			{
				//Code must be present, prevents direction from misaligning
				oldDirection = mDirection;
				mDirection = targetDir;

				rotVal += oldDirection.AngleBetweenTwoVector(mDirection);
				stopRotation = true;
			}
		}
	}
}

void ippMissile::MoveToWayPoint( float x, float y )
{
	wayPoint->SetWaypoint( x, y );
	stopRotation = false;
}