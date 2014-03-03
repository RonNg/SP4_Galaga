#pragma once
#include <GL/freeglut.h>
#include <time.h>

#include "Entities\GameObject.h"
#include <vector>
#include "LoadTGA\LoadTGA.h"

class ippWaypoint;
class ippEnemyGrid;

class ippEnemy
	: public ippGameObject
{
public:
	enum enemyType_t
	{
		GREEN = 0,
		BLUE,
		RED
	};

private:
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
	bool						deleteFlag; // true if wants the objet manager to delete
public:
	std::vector<ippWaypoint*>waypointList;

	ippEnemy( Vec3D position, ippEnemyGrid* theGrid, int type, string tag = "Enemy" );
	~ippEnemy(void);
	
	void SetType ( int type );
	int GetType () { return enemyType; }

	//Adds waypoint into vector list
	void AddWaypoint ( Vec3D waypointPos, float range = 5.0f, string tag = "Default" );
	//loopPos is the origin of the circle
	void AddFlightPath_1();
	void AddFlightPath_2();

	void AddAttackPath_1();

	void ResetFlightPath();

	void Rotation ();

	void Init();
	void Update();
	void Render();
	
};

