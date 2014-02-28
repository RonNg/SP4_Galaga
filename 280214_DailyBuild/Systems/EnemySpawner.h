#pragma once
#include <GL\freeglut.h>

#include "Vec3D.h"
#include <vector>

class ippEnemy;
class ippEnemySpawner
{
private:
	Vec3D position; 
	float prevTime;
	float interval; // Delay in spawning each enemy

	int spawnLimit; // Limits number of spawned enemies.
	int spawned; //Keeps track of number of enemies spawn

	int spawnerID;

	bool activate; 

public:
	ippEnemySpawner ( float x, float y, int spawnerID = -1 );
	~ippEnemySpawner(void);

	
	void SetPosition ( float x, float y ) { position.Set ( x, y, 0.0f ); }
	void SetSpawnLimit ( int spawnLimit ) { this->spawnLimit = spawnLimit; }
	bool IsActivated () { return activate; }
	void SetActivation ( bool activate ) { this->activate = activate; }

	int GetID () { return spawnerID; }

	void Reset ();

	void SetPath ( ippEnemy* enemy, int pathNo );


	/*
	===========
	Spawn

	Place in Update. 
	This function requires the flight path input.
	===========
	*/
	void Spawn ( int pathNo );

	bool FinishSpawn ();


		

	

};

