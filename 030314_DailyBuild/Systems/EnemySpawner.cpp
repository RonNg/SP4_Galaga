#include "EnemySpawner.h"
#include "Entities\AI\Enemy.h"

#include "Managers\ObjectManager.h"
#include "Systems\EnemyGrid.h"

ippEnemySpawner::ippEnemySpawner ( float x, float y, ippEnemyGrid* theGrid, int spawnerID )
	: interval ( 0.1f )
	, spawned ( 0 )
	, spawnNo ( 6 )
	, activate ( false )
	, pathNo ( 1 )
{
	position.Set(x, y, 0.0f);
	this->theGrid = theGrid;
	this->spawnerID = spawnerID;
}

ippEnemySpawner::~ippEnemySpawner(void)
{
}

void ippEnemySpawner::SetPath ( ippEnemy* enemy )
{
	switch ( pathNo )
	{
	case 1:
		enemy->AddFlightPath_1();
		break;
	case 2:
		enemy->AddFlightPath_2();
		break;
	}
}

void ippEnemySpawner::Spawn ()
{
	if ( spawned < spawnNo && activate )
	{
		float now = glutGet ( GLUT_ELAPSED_TIME );

		if ( ( now - prevTime ) > interval * 1000.0f )
		{
			ippEnemy* tempEnemy = new ippEnemy ( position, theGrid, ippEnemy::BLUE );
			SetPath( tempEnemy );

			prevTime = now;

			spawned ++;
		}
	}
}

void ippEnemySpawner::Reset ()
{
	spawned = 0;
	spawnNo = 6 ;
	activate = false;
	pathNo =  1;
}