#include "Missile.h"


ippMissile::ippMissile(void)
{
}

ippMissile::ippMissile ( float speed, int damage, float sizeX, float sizeY )
	:stopRotation ( false )
	,turnSpeed ( 2.0f )
	,rotVal ( 0.0f )
	,tPosition ( NULL )
{
	alive = false;
	this->position = position;
	this->tPosition = tPosition;
	this->direction = direction;
	this->speed = speed;
	this->damage = damage;
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
		// Movement of the missile
		position += direction * speed * Global::timedelta;
	}
}

void ippMissile::Render ( void )
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

		glTexCoord2f(0.0f, 0.0f);	glVertex2f ( 0, 0 );
		glTexCoord2f(0.0f, 1.0f);	glVertex2f ( 0, sizeY );
		glTexCoord2f(1.0f, 1.0f);	glVertex2f ( sizeX, sizeY );
		glTexCoord2f(1.0f, 0.0f);	glVertex2f ( sizeX, 0 );

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable ( GL_BLEND );
	glPopMatrix ();
}

void ippMissile::Rotation()
{
	Vec3D targetDir = wayPoint->position - position;
	Vec3D result = targetDir.crossVec3D(direction);
	result.Normalize();
	targetDir.Normalize();

	if ( !stopRotation )
	{
		if (result.z < 0)
		{
			//cw
			rotVal += turnSpeed;
			direction.Rotate2D(turnSpeed, true);
			Vec3D newResult = targetDir.crossVec3D(direction);
			if ( newResult.z > 0 )
			{
				//Code must be present, prevents direction from misaligning
				oldDirection = direction;
				direction = targetDir;

				rotVal -= oldDirection.AngleBetweenTwoVector(direction);
				stopRotation = true;
			}
		}
		else if ( result.z > 0)
		{
			rotVal -= turnSpeed;
			direction.Rotate2D(-turnSpeed, true);
			Vec3D newResult = targetDir.crossVec3D(direction);
			if ( newResult.z < 0 )
			{
				//Code must be present, prevents direction from misaligning
				oldDirection = direction;
				direction = targetDir;

				rotVal += oldDirection.AngleBetweenTwoVector(direction);
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