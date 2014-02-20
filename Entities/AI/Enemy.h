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
	Vec3D gridPos;
	Vec3D oldDir;
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
		FLYING_TO_GRID,
		FLOATING_AT_GRID,
	};

	ippEnemy( Vec3D thisposition );
	~ippEnemy(void);

	Vec3D GetPos() { return position; }
	float GetPosX() { return position.x; }
	float GetPosY() { return position.y; }
	Vec3D GetGridPos() { return gridPos; }
	float GetGridPosX() { return gridPos.x; }
	float GetGridPosY() { return gridPos.y; }

	void SetPosition( float x, float y ) { position.Set( x ,y, 0 ); }
	void SetPosition( Vec3D pos ) { position.Set( pos.x, pos.y, 0 ); }
	void SetGridPos( float x, float y ) { gridPos.Set( x, y, 0 ); }
	void SetGridPos( Vec3D pos ) { gridPos.Set( pos.x, pos.y, 0 ); }

	float GetTurnSpeed() { return turnSpeed; }
	void SetTurnSpeed( float changespeed ) { turnSpeed = changespeed; }
	int GetState() { return currentState; }
	void StateFloat() { currentState = FLOATING; }
	void StateMove() { currentState = ON_THE_MOVE; }
	void StateFlyToGrid() { currentState = FLYING_TO_GRID; }
	void StateFloatAtGrid() { currentState = FLOATING_AT_GRID; }

	void MoveToWaypoint( float x, float y );
	void MoveToWaypoint( Vec3D point );
	void Rotation();
	
	virtual void Update();
	virtual void Render();
};

