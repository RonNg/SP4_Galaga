#include "Enemy.h"


ippEnemy::ippEnemy( Vec3D thisposition )
:	position( 0.0f, 0.0f, 0.0f )
,	gridPos(0,0,0)
,	rotVal(0.0f)
,	stopRotation(true)
,	turnSpeed(1.0f)
,	currentDir(0, -1, 0)
,   moveSpeed(300.0f)
,	at_waypoint(0)
,	currentState(FLOATING)
{
	srand(time(NULL));
	position = thisposition;
}

ippEnemy::~ippEnemy(void)
{
}

void ippEnemy::MoveToWaypoint( float x, float y )
{
	waypoint.SetWaypoint( x, y );
	stopRotation = false;
}

void ippEnemy::MoveToWaypoint( Vec3D point )
{
	waypoint.SetWaypoint( point.x, point.y );
	stopRotation = false;
}

void ippEnemy::Rotation()
{
	Vec3D targetDir = waypoint.position - position;
	Vec3D result = targetDir.crossVec3D(currentDir);
	result.Normalize();
	targetDir.Normalize();

	if ( !stopRotation )
	{
		if (result.z < 0)
		{
			//cw
			rotVal += turnSpeed;
			currentDir.Rotate2D(turnSpeed, true);
			Vec3D newResult = targetDir.crossVec3D(currentDir);
			if ( newResult.z > 0 )
			{
				//Code must be present, prevents direction from misaligning
				oldDir = currentDir;
				currentDir = targetDir;

				rotVal -= oldDir.AngleBetweenTwoVector(currentDir);
				stopRotation = true;
			}
		}
		else if ( result.z > 0)
		{
			rotVal -= turnSpeed;;
			currentDir.Rotate2D(-turnSpeed, true);
			Vec3D newResult = targetDir.crossVec3D(currentDir);
			if ( newResult.z < 0 )
			{
				//Code must be present, prevents direction from misaligning
				oldDir = currentDir;
				currentDir = targetDir;

				rotVal += oldDir.AngleBetweenTwoVector(currentDir);
				stopRotation = true;
			}
		}
	}
}

void ippEnemy::Update()
{
	printf( "%3.3f, %3.3f\n", position.x, position.y );
	if( !waypoint.Reached(position) )
	{
		Rotation();
		
		Vec3D velocity = currentDir * moveSpeed * Global::timedelta;
		position.Set( position.x + velocity.x,
					position.y + velocity.y, 0);
	}
	else
	{
	}

	//position.printVect();
}

void ippEnemy::Render()
{
	glPushMatrix();
	glTranslatef( position.x, position.y, position.z);
	glRotatef( rotVal, 0.0f, 0.0f, 1.0f );
	glColor4f( 0.0f, 0.0f, 1.0f, 0.6f );
	glBegin(GL_QUADS);
	glTexCoord2f( 0, 1 ); glVertex2f( -10.0f, 10.0f );
	glTexCoord2f( 0, 0 ); glVertex2f( -10.0f, -10.0f );
	glTexCoord2f( 1, 0 ); glVertex2f( 10.0f, -10.0f );
	glTexCoord2f( 1, 1 ); glVertex2f( 10.0f, 10.0f );
	glEnd();
	glPopMatrix();

	waypoint.Render();
}