#pragma once
#include "ippEnemy.h"
#include "ippEnemyGrid.h"
#include <vector>
#include "ippGlobals.h"
#include <math.h>
#include <time.h>

using namespace Global;

class ippEnemyManagerClass
{
private:
	typedef std::vector<ippEnemy*> list_of_enemy;
	list_of_enemy enemyWave_;

	ippEnemyGrid grid_assignment;

	Vec3D* list_of_positions;
	Vec3D spawnerPos;
	Vec3D firstWaypoint;

	int numberOfPoints;

	float pie;			//	value of pie 3.141592654

	float curTime;		//	time updated base on Global::timedelta
	float prevTime;		//	time last called and updated by curTime
	float diffTime;		//	the difference in time between prevTime and curTime

	int wave_num;
	int wave_max;
	int current_state;

	bool activateSpawner;

public:
	double tenDegrees;

	enum availableState_t
	{
		SPAWN_SHIPS = 61,
		SEND_SHIPS_FORTH,
		SEND_SHIPS_BACK,
		ORDER_SHIPS_TO_WAIT,
	};

	ippEnemyManagerClass(void);
	~ippEnemyManagerClass(void);

	void Init( int numberOfEnemies );
	void CreateWaves( int number_of_ships, int enemy_type );
	void Spawner( int number_of_ships, int enemy_type, Vec3D spawnpoint, Vec3D flyThere, float interval = 10.0f ); 
	void Spawner( int number_of_ships, int enemy_type, float spawnX, float spawnY, float flyX, float flyY, float interval = 10.0f ); 
	void SetLoopWaypoints( Vec3D point, bool clockwise, float angle = 6.283185308f, float size = 100.0f );
	void SetLoopWaypoints( float pointX, float pointY, bool clockwise, float angle = 6.283185308f, float size = 100.0f );
	void Update();
	void Render();
};
