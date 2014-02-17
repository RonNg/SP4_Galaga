#include "ippEnemyManagerClass.h"


ippEnemyManagerClass::ippEnemyManagerClass(void)
{
}

ippEnemyManagerClass::~ippEnemyManagerClass(void)
{
	enemyWave_.clear();
}

void ippEnemyManagerClass::Init()
{
}

void ippEnemyManagerClass::CreateWaves( int number_of_enemies, int enemy_type )
{
	for( int counter = 0; counter < number_of_enemies; counter++ )
	{
		enemyWave_.push_back( new ippEnemy() );
	}
}

void ippEnemyManagerClass::Update()
{
	count_down += Global::timedelta;

	for( list_of_enemy::iterator updates_for_enemy = enemyWave_.begin();
		updates_for_enemy != enemyWave_.end(); updates_for_enemy++ )
	{
		(*updates_for_enemy)->Update();
		(*updates_for_enemy)->AI.GetCurrentState();
		(*updates_for_enemy)->AI.GetPreviousState();
	}
}

void ippEnemyManagerClass::Render()
{
	for( list_of_enemy::iterator rendering_for_enemy = enemyWave_.begin();
		rendering_for_enemy != enemyWave_.end(); rendering_for_enemy++ )
	{
		(*rendering_for_enemy)->Render();
	}
}