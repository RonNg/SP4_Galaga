#pragma once
#include <GL/freeglut.h>
#include <time.h>

#include "Entities\GameObject.h"
#include <vector>

class ippWaypoint;

class ippEnemy
	: public ippGameObject
{
private:
	float rotVal;
	float turnSpeed;
	float moveSpeed;
	Vec3D oldDir;
	bool stopRotation;

	
	//For keeping track of waypoint that Enemy is going to
	int waypointIndex;

public:
	std::vector<ippWaypoint*>waypointList;

	ippEnemy( Vec3D position, string tag = "Enemy" );
	~ippEnemy(void);

	
	//Adds waypoint into vector list
	void AddWaypoint ( Vec3D waypointPos, float range = 5.0f, string tag = "Default" );
	//loopPos is the origin of the circle
	void AddFlightPath_1();
	void AddFlightPath_2();
	

	

	void Rotation ();

	void Init();
	void Update();
	void Render();
};

