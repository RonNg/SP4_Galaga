#include "Enemy.h"

#include "Managers\ObjectManager.h"

#include "Systems\EnemyGrid.h"
#include "Vec3D.h"
#include "Waypoint.h"


#include "Globals.h"
using namespace Global;

ippEnemy::ippEnemy( Vec3D position, ippEnemyGrid* theGrid, int type, string tag )
	: rotVal ( 0.0f )
	, turnSpeed ( 10.0f )
	, moveSpeed ( 5.0f )
	, oldDir ( direction )
	, stopRotation ( false )
	, waypointIndex ( 0 )
	, deleteFlag ( false )
{
	srand(time(NULL));

	this->position = position;
	this->tag = tag;

	this->theGrid = theGrid;

	ippObjectManager::GetInstance()->AddObj(this);
	SetCollider2D(20, 20);
	
	SetType(type);

	if ( !LoadTGA( &enemyTexture[0], "Images/AI/Enemy_Red.tga" ) )
	{
		cout << " ERROR LOADING " << endl;
	}

	if ( !LoadTGA( &enemyTexture[1], "Images/AI/Enemy_Red.tga" ) )
	{
		cout << " ERROR LOADING " << endl;
	}

	if ( !LoadTGA( &enemyTexture[2], "Images/AI/Enemy_Red.tga" ) )
	{
		cout << " ERROR LOADING " << endl;
	}

	if ( !LoadTGA( &enemyTexture[3], "Images/AI/Enemy_Red.tga" ) )
	{
		cout << " ERROR LOADING " << endl;
	}
}

ippEnemy::~ippEnemy(void)
{
	ippObjectManager::GetInstance()->DeleteObj(this);
}

void ippEnemy::SetType ( int type )
{
	switch ( type )
	{
	case GREEN:
		enemyType = GREEN;
		break;
	case BLUE:
		enemyType = BLUE;
		break;
	case RED:
		enemyType = RED;
		break;

	}
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
	
	switch ( enemyType )
	{	
	case GREEN:
		waypointList.push_back ( theGrid->RequestSlot(1) );
		break;
	
	case RED:
		waypointList.push_back ( theGrid->RequestSlot(2) );
		break;

	case BLUE:
		waypointList.push_back ( theGrid->RequestSlot(3) );
		break;
	}

	AddAttackPath_1();
	
}
void ippEnemy::AddFlightPath_2 ()
{
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, 450, 0 ) );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 125, 450, 0 ), 10.0f, "Loop" );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 210, 450, 0 ), 10.0f, "Loop" );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 250, 300, 0 ), 10.0f );

		switch ( enemyType )
	{	
	case GREEN:
		waypointList.push_back ( theGrid->RequestSlot(1) );
		break;
	
	case RED:
		waypointList.push_back ( theGrid->RequestSlot(2) );
		break;

	case BLUE:
		waypointList.push_back ( theGrid->RequestSlot(3) );
		break;
	}

}
void ippEnemy::AddAttackPath_1 ()
{
	AddWaypoint ( Vec3D ( 100, 300, 0 ), 5.0f, "Attack" );
	AddWaypoint ( Vec3D ( 200, 600, 0 ), 5.0f, "Exit" );
}
void ippEnemy::ResetFlightPath ()
{
	//std::list<ippWaypoint*>::iterator itr;
	//for ( itr = waypointList.begin(); itr != waypointList.end(); ++ itr )
	//{
	//	//if ( (*itr)->tag.compare("Grid Waypoint") == 0 )
	//	//{
	//	//	//Find the waypoint in grid and set occupied to false
	//	//	(*itr
	//	//}
	//	delete (*itr);
	//  		waypointList.erase(itr);
	//}

	//waypointList.clear();
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
void ippEnemy::Init()
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
			else if ( waypointList[waypointIndex]->tag.compare( "Exit" ) == 0 )
			{
				deleteFlag = true;
				moveSpeed = 10.0f;
				turnSpeed = 10.0f;
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
		else // Last waypoint
		{
			direction.Set ( 0, -1, 0 );
			this->rotVal = 180;
		}
	}
}
void ippEnemy::Render()
{
	for ( int i = 0; i < waypointList.size(); i ++ )
	{
		waypointList[i]->Render();
	}
	// Enable/Disable features
	glEnable(GL_TEXTURE_2D);


	glPushMatrix();
	glTranslatef( position.x, position.y, 0);
	glRotatef( rotVal, 0.0f, 0.0f, 1.0f );
		glBindTexture(GL_TEXTURE_2D, enemyTexture[0].texID);
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
			glBegin(GL_QUADS);
			glTexCoord2f( 0, 1 ); glVertex2f( -10.0f, 10.0f );
			glTexCoord2f( 0, 0 ); glVertex2f( -10.0f, -10.0f );
			glTexCoord2f( 1, 0 ); glVertex2f( 10.0f, -10.0f );
			glTexCoord2f( 1, 1 ); glVertex2f( 10.0f, 10.0f );
			glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}