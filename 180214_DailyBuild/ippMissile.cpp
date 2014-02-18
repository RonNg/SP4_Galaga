#include "ippMissile.h"


ippMissile::ippMissile(void)
{
}

ippMissile::ippMissile ( Vec3D position, Vec3D* tPosition, Vec3D direction,float speed, int damage, float sizeX, float sizeY )
	:stopRotation ( false )
	,turnSpeed ( 2.0f )
	,rotVal ( 0.0f )
{
	this->position = position;
	this->tPosition = tPosition;
	this->direction = direction;
	this->speed = speed;
	this->damage = damage;
	this->sizeX = sizeX;
	this->sizeY = sizeY;

	projectile = new ippQuadClass ();
	wayPoint = new ippWaypoint ();

	projectile->SetLW ( sizeX, sizeY );
}

ippMissile::~ippMissile(void)
{
}

void ippMissile::Update ( void )
{
	if ( oldTargetPosition != Vec3D ( tPosition->x, tPosition->y, tPosition->z ) )
	{
		oldTargetPosition = Vec3D ( tPosition->x, tPosition->y, tPosition->z );
		wayPoint->SetWaypoint( oldTargetPosition.x, oldTargetPosition.y );
		stopRotation = false;
	}

	Rotation ();

	// Movement of the missile
	position += direction * speed * Global::timedelta;

	// Updates the projectile's position
	projectile->SetXY ( position.x, position.y );
}

void ippMissile::Render ( void )
{
	projectile->DrawQuads ();
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
				//direction = targetDir;

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