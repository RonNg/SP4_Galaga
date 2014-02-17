#pragma once
#include "ippEnemy.h"
#include "ippEnemyGrid.h"
#include <vector>
#include "ippGlobals.h"

using namespace Global;

class ippEnemyManagerClass
{
private:
	typedef std::vector<ippEnemy*> list_of_enemy;
	list_of_enemy enemyWave_;

	ippEnemyGrid grid_assignment;

	Vec3D list_of_positions[20];

	int count_down;
	int wave_num;
	int level_num;

public:
	ippEnemyManagerClass(void);
	~ippEnemyManagerClass(void);

	void Init();
	void CreateWaves( int number_of_enemies, int enemy_type );
	void Update();
	void Render();
};
