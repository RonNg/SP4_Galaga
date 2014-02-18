#include "ippEnemyManagerClass.h"


ippEnemyManagerClass::ippEnemyManagerClass(void)
:	fly_through_point(0)
,	count_down(0.0f)
,	time_(0.0f)
,	wave_num(0)
,	level_num(0)
,	current_state(0)
{
}

ippEnemyManagerClass::~ippEnemyManagerClass(void)
{
	enemyWave_.clear();
}

void ippEnemyManagerClass::Init()
{
	for( int i = 0; i < 36; i++ )
	{
		int tempX = sin(i) * 10;
		int tempY = cos(i) * 10;
		list_of_positions[i] = Vec3D( tempX, tempY, 0.0f );
	}
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
		if( (*updates_for_enemy)->at_waypoint == (*updates_for_enemy)->GetTargetWaypoint() )
		{
			fly_through_point++;
			printf( "flying through point %d\n", fly_through_point );
			(*updates_for_enemy)->MoveToWaypoint( list_of_positions[fly_through_point].x, list_of_positions[fly_through_point].y, fly_through_point );
		}
		(*updates_for_enemy)->Update();
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