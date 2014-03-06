#include "EnemySpawner.h"
#include "Entities\AI\Enemy.h"

#include "Managers\ObjectManager.h"
#include "Systems\EnemyGrid.h"

ippEnemySpawner::ippEnemySpawner ( float x, float y, ippEnemyGrid* theGrid, int spawnerID )
	: interval ( 0.15f )
	, spawned ( 0 )
	, spawnNo ( 6 )
	, activate ( false )
	, pathNo ( 1 )
	, spawnDelay ( 0.0f )
	, startSpawning ( false )
	, prevTime ( 0.0f )
{
	position.Set(x, y, 0.0f);
	this->theGrid = theGrid;
	this->spawnerID = spawnerID;
}

ippEnemySpawner::~ippEnemySpawner (void)
{
}


void ippEnemySpawner::Spawn ()
{
	
	float now = glutGet ( GLUT_ELAPSED_TIME );

	if ( ( now - prevTime ) > spawnDelay ) 
	{
		startSpawning = true;
	}

	if ( spawned < spawnNo && activate && startSpawning )
	{
		if ( ( now - prevTime ) > interval * 1000.0f )
		{
			ippEnemy* tempEnemy = new ippEnemy ( position, theGrid, type );
			
			tempEnemy->AddFlightPath(pathNo);

			prevTime = now;

			spawned ++;
		}
	}
}

void ippEnemySpawner::Reset ()
{
	interval = 0.15f;
	spawned =  0;
	spawnNo = 6; 
	activate = false;
	pathNo = 1;
	spawnDelay = 0.0f;
	startSpawning = false;
	prevTime = glutGet(GLUT_ELAPSED_TIME);
}