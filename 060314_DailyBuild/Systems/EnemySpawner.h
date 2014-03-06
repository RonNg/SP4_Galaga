#pragma once
#include <GL\freeglut.h>

#include "Vec3D.h"
#include <vector>

class ippEnemy;
class ippEnemyGrid;

class ippEnemySpawner
{
private:
	Vec3D position; 
	float prevTime;
	float interval; // Delay in spawning each enemy
	
	float spawnDelay; // Spawn delay in seconds
	bool startSpawning; 

	int spawnerID;
	bool activate; 

	int spawnNo; // Limits number of spawned enemies.
	int spawned; //Keeps track of number of enemies spawn
	int pathNo; // Flight path number
	int type; // Enemy Type


	ippEnemyGrid*	theGrid;
public:
	ippEnemySpawner ( float x, float y, ippEnemyGrid* theGrid, int spawnerID = -1 );
	~ippEnemySpawner(void);

	
	void SetPosition ( float x, float y ) { position.Set ( x, y, 0.0f ); }
	void SetSpawnNo ( int spawnNo ) { this->spawnNo = spawnNo; }
	bool IsActivated () { return activate; }
	void SetActivation ( bool activate ) { this->activate = activate; }
	void SetPathNo ( int pathNo ) { this->pathNo = pathNo; }
	void SetType ( int type ) { this->type = type; }
	void SetDelay ( float spawnDelay) { this->spawnDelay= spawnDelay * 1000.0f; }

	int GetID () { return spawnerID; }

	void Reset ();

	void SetPath ( ippEnemy* enemy );


	/*
	===========
	Spawn

	Place in Update. 
	This function requires the flight path input.
	===========
	*/
	void Spawn ();

};

