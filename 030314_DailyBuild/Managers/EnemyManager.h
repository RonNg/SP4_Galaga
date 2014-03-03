#pragma once

#include "Entities\AI\Enemy.h"

#include <vector>
#include <math.h>
#include <time.h>

class ippEnemyManager
{
private:
	int totalEnemy;
	float prevTime; // For spawning enemies at intervals
	float interval; // interval in seconds for spawning of enemies
	int index;

public:
	ippEnemyManager(void);
	~ippEnemyManager(void);

	//std::vector< ippEnemy* >enemyList;

	//void AddEnemy ( int enemyNo );
	//void SpawnEnemy ( Vec3D spawnPos );

	//void Init ();
	//void Update();

};

