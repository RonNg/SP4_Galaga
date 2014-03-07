#include "Enemy.h"

#include "Managers\ObjectManager.h"
#include "Managers\GameManager.h"

#include "Systems\EnemyGrid.h"
#include "Vec3D.h"
#include "Waypoint.h"

#include "Globals.h"
using namespace Global;

ippEnemy::ippEnemy( Vec3D position, ippEnemyGrid* theGrid, int type, string tag )
	: size ( 12.5f ) 
	, rotVal ( 0.0f )
	, turnSpeed ( 15.0f )
	, moveSpeed ( 10.0f )
	, oldDir ( direction )
	, stopRotation ( false )
	, waypointIndex ( 0 )
	, attackPathAdd ( false )
	, shootOnce ( false )
{
	srand(time(NULL));

	this->position = position;
	this->tag = tag;
	this->theGrid = theGrid;


	ippObjectManager::GetInstance()->AddObj(this);
	SetCollider2D ( size + 7.5f, size + 7.5f );
	SetType(type);
	
	prevTime = glutGet(GLUT_ELAPSED_TIME);
	attackInterval = 4 * 1000.0f;

	if ( !LoadTGA( &enemyTexture[RED_TEX], "Images/AI/Enemy_Red.tga" ) )
	{
		cout << " ERROR LOADING " << endl;
	}

	if ( !LoadTGA( &enemyTexture[BLUE_TEX], "Images/AI/Enemy_Blue.tga" ) )
	{
		cout << " ERROR LOADING " << endl;
	}

	if ( !LoadTGA( &enemyTexture[GREEN_TEX], "Images/AI/Enemy_Green.tga" ) )
	{
		cout << " ERROR LOADING " << endl;
	}

	if ( !LoadTGA( &enemyTexture[PURPLE_TEX], "Images/AI/Enemy_Green.tga" ) )
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

void ippEnemy::AddFlightPath ( int pathNo )
{
	switch ( pathNo )
	{
	case 1:
		FlightPath_1();
		break;
	case 2:
		FlightPath_2();
		break;
	case 3:
		FlightPath_3();
		break;
	case 4:
		FlightPath_4();
		break;
	case 5:
		FlightPath_5();
		break;
	case 6:
		FlightPath_6();
		break;
	}
}

void ippEnemy::FlightPath_1 ()
{
	AddWaypoint ( Vec3D ( 200, 400, 0 ), 15.0f );
	AddWaypoint ( Vec3D ( 125, 400, 0 ), 15.0f, "Loop" );
	AddWaypoint ( Vec3D ( 210, 400, 0 ), 15.0f, "Loop" );
	AddWaypoint ( Vec3D ( 250, 250, 0 ), 15.0f );
	
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
void ippEnemy::FlightPath_2 ()
{
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, 400, 0 ), 15.0f );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 125, 400, 0 ), 15.0f, "Loop" );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 210, 400, 0 ), 15.0f, "Loop" );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 250, 250, 0 ), 15.0f );

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
void ippEnemy::FlightPath_3 ()
{
	AddWaypoint ( Vec3D ( 200, 300, 0 ), 15.0f, "Loop" );

	AddWaypoint ( Vec3D ( 200, 400, 0 ), 15.0f, "Loop" );
	AddWaypoint ( Vec3D ( 300, 400, 0 ), 15.0f, "Loop" );

	AddWaypoint ( Vec3D ( 300, 300, 0 ), 15.0f, "Loop" );

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
void ippEnemy::FlightPath_4 ()
{
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, 300, 0 ), 15.0f, "Loop" );

	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, 400, 0 ), 15.0f, "Loop" );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 300, 400, 0 ), 15.0f, "Loop" );

	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 300, 300, 0 ), 15.0f, "Loop" );

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
void ippEnemy::FlightPath_5 ()
{
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, Global::HEIGHT_RESOLUTION - 130, 0 ), 15.0f, "Loop" );
	AddWaypoint ( Vec3D ( 200, Global::HEIGHT_RESOLUTION - 250, 0 ), 15.0f, "Loop" );

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
void ippEnemy::FlightPath_6 ()
{
	AddWaypoint ( Vec3D ( 200, Global::HEIGHT_RESOLUTION - 130, 0 ), 15.0f, "Loop" );
	AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, Global::HEIGHT_RESOLUTION - 250, 0 ), 15.0f, "Loop" );

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

void ippEnemy::AddAttackPath ( int pathNo )
{
	switch ( pathNo )
	{
	case 1:
		AddWaypoint ( Vec3D ( 100, 300, 0 ), 5.0f );
		AddWaypoint ( Vec3D ( 200, 500, 0 ), 5.0f, "Shoot" );
		AddWaypoint ( Vec3D ( RNG(0, 300), 800, 0 ), 5.0f );
		AddWaypoint ( Vec3D ( 400, 900, 0 ), 5.0f, "Exit" );
		break;
	case 2:
		AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 100, 300, 0 ), 5.0f );
		AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, 500, 0 ), 5.0f, "Shoot" );
		AddWaypoint ( Vec3D ( RNG(0, 300), 800, 0 ), 5.0f );
		AddWaypoint ( Vec3D ( 400, 900, 0 ), 5.0f, "Exit" );
		break;
	case 3:
		AddWaypoint ( Vec3D ( 200, 400, 0 ), 15.0f );
		AddWaypoint ( Vec3D ( 105, 400, 0 ), 15.0f,  "Shoot" );
		AddWaypoint ( Vec3D ( 200, 400, 0 ), 15.0f);
		AddWaypoint ( Vec3D ( RNG( 300, 700), 800, 0 ), 15.0f );
		AddWaypoint ( Vec3D ( 400, 900, 0 ), 15.0f, "Exit" );
		break;
	case 4:
		AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, 400, 0 ), 15.0f );
		AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 105, 400, 0 ), 15.0f, "Shoot");
		AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, 400, 0 ), 15.0f );
		AddWaypoint ( Vec3D ( RNG(300, 700), 800, 0 ), 15.0f );
		AddWaypoint ( Vec3D ( 400, 900, 0 ), 15.0f, "Exit" );
		break;

	case 5:
		AddWaypoint ( Vec3D ( 200, 200, 0 ), 15.0f, "Shoot" );
		AddWaypoint ( Vec3D ( Global::WIDTH_RESOLUTION - 200, 300, 0 ), 15.0f);
		AddWaypoint ( Vec3D ( RNG(300, 500), 800, 0 ), 15.0f );

		AddWaypoint ( Vec3D ( 400, 800, 0 ), 15.0f );
		AddWaypoint ( Vec3D ( 400, 900, 0 ), 15.0f, "Exit" );
		break;

	case 6:
		AddWaypoint ( Vec3D (Global::WIDTH_RESOLUTION - 200, 200, 0 ), 15.0f, "Shoot" );
		AddWaypoint ( Vec3D ( 200, 300, 0 ), 15.0f);
		AddWaypoint ( Vec3D ( RNG(300, 500), 800, 0 ), 15.0f );

		AddWaypoint ( Vec3D ( 400, 800, 0 ), 15.0f );
		AddWaypoint ( Vec3D ( 400, 900, 0 ), 15.0f, "Exit" );
		break;

		
	}
	
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
void ippEnemy::Update_Movement ()
{
	if ( waypointList[waypointIndex]->tag.compare( "Exit" ) == 0 )
	{
		deleteFlag = true;
	}
	else if ( waypointList[waypointIndex]->tag.compare ( "Shoot" ) == 0 )
	{
		//Do shooting here
		if ( !shootOnce )
		{
			//Gets the position of the player and fires in the direction of player.
			Vec3D playerPos = ippObjectManager::GetInstance()->GetRandomObjByTag("Player")->GetPosition();
			Vec3D fireDirection = playerPos - this->position;

			fireDirection.Normalize();
			fireDirection.x *= 0.25f;
		
			ippGameManager::GetInstance()->FireBullet ( this->GetPosition(), fireDirection );


			shootOnce = true;
		}
	}
}
void ippEnemy::Update()
{
	//Checks if waypoint list is empty
	if ( waypointList.size() != 0 )
	{
		//If waypoint hasn't been reached yet and is activated, proceed to move towards waypoint
		if( !waypointList[waypointIndex]->Reached(position) && waypointList[waypointIndex]->IsActivated() )
		{
			Update_Movement();

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

			if ( waypointList[waypointIndex]->tag.compare ( "Grid Waypoint" ) == 0 )
			{
				this->position = waypointList[waypointIndex]->position;
			}
			
			if ( !attackPathAdd )
			{
				float now = glutGet(GLUT_ELAPSED_TIME);
				if (  ( now - prevTime ) > attackInterval )
				{
					prevTime = now;

					//Does a RNG here to see if the enemy attacks.
					int chance = rand() % 100;
					//Random attack here because it's the last point, time to add teh path
					if ( chance > 75  )
					{
						//Plays sound since enemy is now attacking player.
						bool playOnce = true;
						if ( playOnce )
						{
							Sound_Attack = Global::theSoundEngine->play2D("Sounds/Enemy_Flying.mp3",false);
							playOnce = false;
						}

						srand(time(NULL));
						int pathNo = rand() % 6 + 1;
						AddAttackPath(pathNo);
						attackPathAdd = true;
					}
				}
			}
		}
	}
}
void ippEnemy::Render()
{
	
	// Enable/Disable features
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef( position.x, position.y, 0);
	glRotatef( rotVal, 0.0f, 0.0f, 1.0f );
	
	switch ( enemyType )
	{
	case RED:
		glBindTexture(GL_TEXTURE_2D, enemyTexture[RED_TEX].texID);
		break;
	case BLUE:
		glBindTexture(GL_TEXTURE_2D, enemyTexture[BLUE_TEX].texID);
		break;
	case GREEN:
		glBindTexture(GL_TEXTURE_2D, enemyTexture[GREEN_TEX].texID);
		break;
	}		
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
			glBegin(GL_QUADS);
			glTexCoord2f( 0, 1 ); glVertex2f( -size, size );
			glTexCoord2f( 0, 0 ); glVertex2f( -size, -size );
			glTexCoord2f( 1, 0 ); glVertex2f( size, -size);
			glTexCoord2f( 1, 1 ); glVertex2f( size, size);
			glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);


}