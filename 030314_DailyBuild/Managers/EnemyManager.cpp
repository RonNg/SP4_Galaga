#include "EnemyManager.h"

#include <windows.h>
ippEnemyManager::ippEnemyManager(void)
	: totalEnemy ( 0 )
	, index ( 0 )
{
	prevTime = glutGet(GLUT_ELAPSED_TIME);
}


ippEnemyManager::~ippEnemyManager(void)
{
}

//void ippEnemyManager::Init ()
//{
//}
//
//void ippEnemyManager::Update ()
//{
//}
//
//void ippEnemyManager::AddEnemy ( int enemyNo )
//{
//	this->totalEnemy += enemyNo;
//}
//void ippEnemyManager::SpawnEnemy ( Vec3D spawnPos )
//{
//	if ( index < totalEnemy )
//	{
//		float now = glutGet(GLUT_ELAPSED_TIME);
//
//		if ( (now - prevTime) > 0.1 * 1000.0f )
//		{
//			enemyList.push_back( new ippEnemy ( spawnPos ) );
//			enemyList.back()->AddFlightPath_1();
//
//			prevTime = now;
//			index ++;
//		}
//	}
//}