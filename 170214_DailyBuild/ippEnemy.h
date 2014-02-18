#pragma once
#include <GL/freeglut.h>
#include "ippBasicAI.h"
#include "Vec3D.h"
#include "ippWaypoint.h"
#include <time.h>

class ippEnemy
{
private:
	Vec3D position;
	Vec3D currentDir;
	Vec3D oldDir;
	int time_idling;
	float rotVal;
	float turnSpeed;
	float moveSpeed;
	bool stopRotation;

	int target_waypoint;

public:
	ippWaypoint waypoint;
	ippBasicAI AI;
	
	int at_waypoint;

	ippEnemy(void);
	~ippEnemy(void);

	int GetTargetWaypoint() { return target_waypoint; }
	float GetPosX() { return position.x; }
	float GetPosY() { return position.y; }
	float GetTurnSpeed() { return turnSpeed; }
	void SetPosition( float x, float y ) { position.Set(x ,y, 0 ); }
	void SetTurnSpeed( float changespeed ) { turnSpeed = changespeed; }

	void MoveToWaypoint( float x, float y, int waypoint_number );
	void Rotation();
	
	virtual void Update();
	virtual void Render();
};

