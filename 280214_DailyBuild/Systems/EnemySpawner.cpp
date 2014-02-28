#include "EnemySpawner.h"
#include "Entities\AI\Enemy.h"

#include "Managers\ObjectManager.h"

ippEnemySpawner::ippEnemySpawner ( float x, float y, int spawnerID )
	: interval ( 0.1f )
	, spawned ( 0 )
	, spawnLimit ( 6 )
{
	position.Set(x, y, 0.0f);
	this->spawnerID = spawnerID;
}


ippEnemySpawner::~ippEnemySpawner(void)
{
}

void ippEnemySpawner::SetPath ( ippEnemy* enemy, int pathNo )
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

void ippEnemySpawner::Spawn ( int pathNo )
{
	
	//if finish spawning, deactivates the spawner
 	activate = !FinishSpawn();

	if ( activate )
	{
		float now = glutGet ( GLUT_ELAPSED_TIME );

		if ( ( now - prevTime ) > interval * 1000.0f )
		{
			ippEnemy* tempEnemy = new ippEnemy ( position );
			tempEnemy->AddFlightPath_1();

			prevTime = now;

			spawned ++;
			int spawnLimit; // Limits number of spawned enemies.
		}
	}
}
void ippEnemySpawner::Reset ()
{
	spawned = 0;
}
bool ippEnemySpawner::FinishSpawn ()
{
	if ( spawned >= spawnLimit )
	{
		return true;
	}

	return false;
}




