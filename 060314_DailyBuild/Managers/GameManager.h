#pragma once
#include "Singleton.h"

#include <vector>

class ippEnemySpawner;
class ippEnemyGrid;
class ippPowerUpManager;
class ippStarManager;

class ippGameManager
	: public ippSingleton<ippGameManager>
{
private:

	bool loadFinish; // a boolean that makes sure load level runs only once
	std::vector<ippEnemySpawner*>spawnerList;
	ippEnemyGrid* theGrid;

	float prevTime;

	//Enemy Count
	int greenNo;
	int redNo;
	int blueNo;
	int totalNo;




	//FOR RANDOM GENERATION OF LEVELS

	/*
	========================
	
	When spawners spawn enemies, they must deduct from this pool 
	Safeguard in case of over spawning.
	This pool is reset after every wave.

	The number of enemies in this pool available is as follow
	Green = 4;
	Red = 16;
	Blue = 20;

	Total = 50 enemies at any one wave.
	========================
	*/
	int greenPool;
	int redPool;
	int bluePool; 

	//Wave Control
	int waveNo; // Current wave number

	//Garbage collector interval
	float gcPrevTime;


public:
	ippGameManager(void);
	~ippGameManager(void);

	void Init ();
	void Update();
	void Render ();

	void SpawnerLoad ( int index );
	
	void LoadLevel ();
	void LoadPreset_1 ( int difficulty );
	void LoadPreset_2( int difficulty );
	void TestPreset();

	ippPowerUpManager*		powerupManager;
	ippStarManager*			starManager;

	void Reset(); // Reset everything to prepare for next wave
	void Spawn ();

	void DeleteFlagged();
	void DeleteOutOfScreen();



};

