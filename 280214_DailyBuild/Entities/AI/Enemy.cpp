#include "Enemy.h"

#include "Managers\ObjectManager.h"

#include "Vec3D.h"
#include "Waypoint.h"

#include "Globals.h"
using namespace Global;

ippEnemy::ippEnemy( Vec3D position, string tag )
	: rotVal ( 0.0f )
	, turnSpeed ( 10.0f )
	, moveSpeed ( 5.0f )
	, oldDir ( direction )
	, stopRotation ( false )
	, waypointIndex ( 0 )
{
	srand(time(NULL));

	this->position = position;
	this->tag = tag;

	ippObjectManager::GetInstance()->AddObj(this);
	SetCollider2D(20, 20);
}

ippEnemy::~ippEnemy(void)
{
	ippObjectManager::GetInstance()->DeleteObj(this);
}

void ippEnemy::AddWaypoint( Vec3D waypointPos, float range, string tag )
{
	waypointList.push_back( new ippWaypoint( waypointPos.x, waypointPos.y, range, tag ) );
}
void ippEnemy::AddFlightPath_1 ()
{
	AddWaypoint ( Vec3D ( 200, 450, 0 ) );
	AddWaypoint ( Vec3D ( 125, 450, 0 ), 10.0f, "Loop" );
	AddWaypoint ( Vec3D ( 210, 450, 0 ), 10.0f, "Loop" );
	AddWaypoint ( Vec3D ( 250, 300, 0 ), 10.0f );
}

void ippEnemy::AddFlightPath_2 ()
{
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, 450, 0 ) );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 125, 450, 0 ), 10.0f, "Loop" );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 210, 450, 0 ), 10.0f, "Loop" );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 250, 300, 0 ), 10.0f );
}

void ippEnemy::Rotation()
{
	Vec3D targetDir = waypointList[waypointIndex]->position - position;
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
				oldDir = direction;
				direction = targetDir;

				rotVal -= oldDir.AngleBetweenTwoVector(direction);
				stopRotation = true;
			}
		}
		else if ( result.z > 0)
		{
			rotVal -= turnSpeed;;
			direction.Rotate2D(-turnSpeed, true);
			Vec3D newResult = targetDir.crossVec3D(direction);
			if ( newResult.z < 0 )
			{
				//Code must be present, prevents direction from misaligning
				oldDir = direction;
				direction = targetDir;

				rotVal += oldDir.AngleBetweenTwoVector(direction);
				stopRotation = true;
			}
		}
	}
}

void ippEnemy::Init ()
{
}

void ippEnemy::Update()
{
	//Checks if waypoint list is empty
	if ( waypointList.size() != 0 )
	{
		//If waypoint hasn't been reached yet and is activated, proceed to move towards waypoint
		if( !waypointList[waypointIndex]->Reached(position) && waypointList[waypointIndex]->IsActivated() )
		{
			if ( waypointList[waypointIndex]->tag.compare( "Loop" ) == 0  )
			{
				moveSpeed = 10.0f;
				turnSpeed = 13.0f;
			}
			else
			{
				moveSpeed = 10.0f;
				turnSpeed = 10.0f;
			}

			Rotation();

			Vec3D velocity = direction * moveSpeed * Global::timedelta;
			position.Set( position.x + velocity.x,
				position.y + velocity.y, 0);
		}
		//Waypoint list returns the number of elements. -1 to account for array starting from 0
		else if ( waypointIndex < waypointList.size() - 1 ) 	
		{
			//When moving to next waypoint, stopRotation must be set to false
			//to enable rotation again.
			waypointIndex ++;
			stopRotation = false;
		}
	}
}

void ippEnemy::Render()
{

	
	for ( int i = 0; i < waypointList.size(); i ++ )
	{
		waypointList[i]->Render();
	}

	glPushMatrix();
	
	glTranslatef( position.x, position.y, 0);
	glRotatef( rotVal, 0.0f, 0.0f, 1.0f );
	
		glColor4f( 0.0f, 0.0f, 1.0f, 0.6f );
			glBegin(GL_QUADS);
			glTexCoord2f( 0, 1 ); glVertex2f( -10.0f, 10.0f );
			glTexCoord2f( 0, 0 ); glVertex2f( -10.0f, -10.0f );
			glTexCoord2f( 1, 0 ); glVertex2f( 10.0f, -10.0f );
			glTexCoord2f( 1, 1 ); glVertex2f( 10.0f, 10.0f );
			glEnd();
	glPopMatrix();

}