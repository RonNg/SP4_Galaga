#pragma once
#include "Enemy.h"
#include "EnemyGrid.h"
#include <vector>
#include "Globals.h"
#include <math.h>
#include <time.h>

using namespace Global;

class ippEnemyManagerClass
{
private:
	typedef std::vector<ippEnemy*> list_of_enemy;
	list_of_enemy enemyWave_;

	ippEnemyGrid* theGrid;

	Vec3D* list_of_positions;
	Vec3D spawnerPos;
	Vec3D firstWaypoint;

	int waypointTracker;

	int numberOfPoints;
	int lastPoint;

	float pie;			//	value of pie 3.141592654

	float curTime;		//	time updated base on Global::timedelta
	float prevTime;		//	time last called and updated by curTime
	float diffTime;		//	the difference in time between prevTime and curTime

	int wave_num;
	int wave_max;
	int current_state;

	bool activateSpawner;
	bool resetAt;

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

	int GetWaypointTracker() { return waypointTracker; }
	ippEnemyGrid* GetGrid() { return theGrid; }

	void Init();
	void InitGrid( float xSize, float ySize, int xArray, int yArray, float xShip, float yShip, float xGrid, float yGrid );
	void InitGrid( float xSize, float ySize, int xArray, int yArray, float xShip, float yShip, Vec3D gridPos );

	void CreateWaves( int number_of_ships, int enemy_type );
	void ChangeLastPoint( int number );
	void ActivateSpawn();

	Vec3D AssignGridSlot( int num );

	float DegreeTen( float num );
	
	void Spawner( int number_of_ships, int enemy_type, Vec3D spawnpoint, float interval = 10.0f ); 
	void Spawner( int number_of_ships, int enemy_type, float spawnX, float spawnY, float interval = 10.0f );
	void SetSpawnPoint( Vec3D point );
	void SetSpawnPoint( float pointX, float pointY );
	void SetSpawnInterval( float timeDelay );
	void SetNumberOfSpawn( int limitNumber );
	
	void ResetTracker();
	void AddWaypoint( Vec3D point );
	void AddWaypoint( float pointX, float pointY );
	void AddLoop( Vec3D point, bool clockwise, int stopHere, int angleBreak = 0, float size = 100.0f, float angle = 6.283185308f );
	void AddLoop( float pointX, float pointY, bool clockwise, int stopHere, int angleBreak = 0, float size = 100.0f, float angle = 6.283185308f );
	
	void ClearWaypoints();
	void ResetWaypointsAt( Vec3D point );
	void ResetWaypointsAt( float pointX, float pointY );
	void ShowWaypoints();
	void Update();
	void Render();
	void RenderWaypoints();
};
