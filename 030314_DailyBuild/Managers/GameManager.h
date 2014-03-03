#pragma once
#include "Singleton.h"

#include <vector>

class ippEnemySpawner;
class ippEnemyGrid;

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

	//Wave Control
	int waveNo; // Current wave number


public:
	ippGameManager(void);
	~ippGameManager(void);

	void Init ();
	void Update();
	void Render ();

	void LoadLevel ();
	void LoadLevel_1 ();
	void LoadLevel_2();


	void Reset(); // Reset everything to prepare for next wave
	void Spawn ();

};

