#pragma once
#include "Singleton.h"

#include "Systems\EnemySpawner.h"

class ippGameManager
	: public ippSingleton<ippGameManager>
{
private:
	int waveNo; 
	int levelNo;
	int difficultyMod;

	std::vector<ippEnemySpawner*>spawnerList;
public:
	ippGameManager(void);
	~ippGameManager(void);

	void Init ();
	void Update ();



};

