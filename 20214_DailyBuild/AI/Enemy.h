#pragma once
#include <GL/freeglut.h>
#include "BasicAI.h"
#include "Vec3D.h"
#include "Waypoint.h"
#include <time.h>

#include "Globals.h"
using namespace Global;

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
	
	int currentState;

public:
	ippWaypoint waypoint;
	ippBasicAI AI;
	
	int at_waypoint;

	enum availableState_t
	{
		FLOATING = 809,
		ON_THE_MOVE,
	};

	ippEnemy( Vec3D thisposition );
	~ippEnemy(void);

	Vec3D GetPos() { return position; }
	float GetPosX() { return position.x; }
	float GetPosY() { return position.y; }
	float GetTurnSpeed() { return turnSpeed; }
	void SetPosition( float x, float y ) { position.Set(x ,y, 0 ); }
	void SetTurnSpeed( float changespeed ) { turnSpeed = changespeed; }
	int GetState() { return currentState; }
	void StateFloat() { currentState = FLOATING; }
	void StateMove() { currentState = ON_THE_MOVE; }

	void MoveToWaypoint( float x, float y );
	void MoveToWaypoint( Vec3D point );
	void Rotation();
	
	virtual void Update();
	virtual void Render();
};

