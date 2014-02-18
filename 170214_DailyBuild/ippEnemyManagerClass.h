#pragma once
#include "ippEnemy.h"
#include "ippEnemyGrid.h"
#include <vector>
#include "ippGlobals.h"
#include <math.h>

using namespace Global;

class ippEnemyManagerClass
{
private:
	typedef std::vector<ippEnemy*> list_of_enemy;
	list_of_enemy enemyWave_;

	ippEnemyGrid grid_assignment;

	Vec3D list_of_positions[36];

	int fly_through_point;

	float count_down;
	float time_;
	int wave_num;
	int level_num;
	int current_state;

public:

	enum availableState_t
	{
		SPAWN_SHIPS = 61,
		SEND_SHIPS_FORTH,
		SEND_SHIPS_BACK,
		ORDER_SHIPS_TO_WAIT,
	};

	ippEnemyManagerClass(void);
	~ippEnemyManagerClass(void);

	void Init();
	void CreateWaves( int number_of_enemies, int enemy_type );
	void Update();
	void Render();
};
