#pragma once
#include "Singleton.h"

#include "Systems\EnemySpawner.h"

class ippGameManager
	: public ippSingleton<ippGameManager>
{
private:
	int waveNo; 
	int levelNo;

	bool loadFinish; // a boolean that makes sure load level runs only once
	
	std::vector<ippEnemySpawner*>spawnerList;
public:
	ippGameManager(void);
	~ippGameManager(void);

	void Init ();
	void Update();


	void StartNextWave ();
	void StartNextLevel ();

	void LoadLevel ();

};

