#pragma once
#include <GL/freeglut.h>
#include <time.h>

#include "Entities\GameObject.h"
#include <vector>
#include "LoadTGA\LoadTGA.h"
#include "Entities\Weapons\Bullet.h"

class ippWaypoint;
class ippEnemyGrid;

class ippEnemy
	: public ippGameObject
{
public:
	enum enemyType_t
	{
		GREEN = 1,
		RED,
		BLUE
		
	};

	enum enemyTexture_t
	{
		GREEN_TEX = 0,
		PURPLE_TEX,
		RED_TEX,
		BLUE_TEX
	};
	
	enum enemyState_t
	{
		MOVING = 0,
		ATTACK
	};

private:
	float						size;
	float						rotVal;
	float						turnSpeed;
	float						moveSpeed;
	Vec3D						oldDir;
	bool						stopRotation;
	//Variables for interaction with grid
	ippEnemyGrid*				theGrid;
	//For keeping track of waypoint that Enemy is going to
	int							waypointIndex;
	enemyType_t					enemyType;
	 
	TextureImage				enemyTexture[4];  //3 textures, red blue and green
	
	enemyState_t				enemyState;
	// Interval in which the enemy does a RNG to see if it attacks or not
	float						prevTime;
	float						attackInterval;   
	bool						attackPathAdd;

	//Weapon
	std::vector<ippBullet*>		bullet;

public:
	std::vector<ippWaypoint*>waypointList;

	ippEnemy( Vec3D position, ippEnemyGrid* theGrid, int type, string tag = "Enemy" );
	~ippEnemy(void);
	
	void SetType ( int type );
	int GetType () { return enemyType; }

	//Adds waypoint into vector list
	void AddWaypoint ( Vec3D waypointPos, float range = 5.0f, string tag = "Default" );
	//loopPos is the origin of the circle
	void AddFlightPath ( int pathNo );
	void FlightPath_1();
	void FlightPath_2();
	void FlightPath_3();
	void FlightPath_4();
	void FlightPath_5();
	void FlightPath_6();

	void AddAttackPath ( int pathNo );
	void AttackPath_1();
	void AttackPath_2();
	
	void ResetFlightPath();

	void Rotation ();

	//Update movement based on where the enemy is
	void Update_Movement();

	void Init();
	void Update();
	void Render();
	
};

