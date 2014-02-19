#include "ippEnemyManagerClass.h"


ippEnemyManagerClass::ippEnemyManagerClass(void)
:	numberOfPoints(62)
,	curTime(0.0f)
,	prevTime(0.0f)
,	diffTime(0.0f)
,	wave_num(0)
,	current_state(0)
,	pie(3.141592654)
,	tenDegrees(0.17453292522222222222222222222222)
,	activateSpawner(false)
{
	srand(time(NULL));
}

ippEnemyManagerClass::~ippEnemyManagerClass(void)
{
	if( list_of_positions != NULL )
	{
		delete [] list_of_positions;
	}
	enemyWave_.clear();
}

void ippEnemyManagerClass::Init( int numberOfEnemies )
{
	int value = 2 * pie * 10;
	list_of_positions = new Vec3D[ numberOfPoints + 1 ];				//	CREATING ARRAY BASED ON SIZE OF TURNING POINT
	wave_max = numberOfEnemies;											//	LIMIT THE NUMBER OF ENEMY SHIPS SPAWN IN ONE WAVE
	int num = 0;

	SetLoopWaypoints( 200.0f, 300.0f, true, 18 * tenDegrees, 100.0f );
	//	=	=	=	=	=	THIS CODE IS FOR DEBUGGING VALUES	=	=	=	=	=
	//for( int i = 0; i < numberOfPoints; i++ )
	//{
	//	float angle = -i;
	//	list_of_positions[i] = Vec3D( 100 * cos(angle)+400, 100 * sin(angle)+300, 0.0f );
	//}
	//	=	=	=	=	=	THIS CODE IS FOR DEBUGGING VALUES	=	=	=	=	=
}

void ippEnemyManagerClass::CreateWaves( int number_of_ships, int enemy_type )
{
	for( int counter = 0; counter < number_of_ships; counter++ )
	{
		Vec3D tempPos = Vec3D( rand()%200+300, rand()%200+200, 0.0f );
		enemyWave_.push_back( new ippEnemy( tempPos ) );
		enemyWave_.at( counter )->MoveToWaypoint( list_of_positions[counter].x, list_of_positions[counter].y );
	}
}

void ippEnemyManagerClass::Spawner( int number_of_ships, int enemy_type, Vec3D spawnpoint, Vec3D flyThere, float interval )
{
	wave_max = number_of_ships;
	spawnerPos = spawnpoint;
	firstWaypoint = flyThere;
	diffTime = interval;
}

void ippEnemyManagerClass::Spawner( int number_of_ships, int enemy_type, float spawnX, float spawnY, float flyX, float flyY, float interval )
{
	wave_max = number_of_ships;
	spawnerPos = Vec3D( spawnX, spawnY, 0.0f );
	firstWaypoint = Vec3D( flyX, flyY, 0.0f );
	diffTime = interval;
}

void ippEnemyManagerClass::SetLoopWaypoints( Vec3D point, bool clockwise, float angle, float size )
{
	//	=	=	=	=	=	EXTRA INFORMATION	=	=	=	=	=
	//	the for() loop below
	//	double angle is the angle of how far you want the ship to fly around
	//	if you want a full cycle, use angle <= 2 * pie
	//	if you want a half cycle, use angle <= pie
	//	
	//	as for the angle increment, angle += 0.1
	//	this is for how defined you want the points to be
	//	it can be as small as 0.001
	//	and biggest is recommended to be 0.1
	//	because 1.0 causes a huge jump from one point to another
	//	=	=	=	=	=	EXTRA INFORMATION	=	=	=	=	=
	int num = 0;
	if( clockwise )
	{
		for( double tempAngle = 0; tempAngle <= angle; tempAngle += 0.1 )		//	CREATE WAYPOINTS BASED ON CIRCLE FORMULA
		{
			list_of_positions[num] = Vec3D( size * cos(tempAngle) + point.x, size * sin(tempAngle) + point.y, 0.0f );
			num++;
		}
	}
	else
	{
		for( double tempAngle = 0; tempAngle <= angle; tempAngle += 0.1 )
		{
			list_of_positions[num] = Vec3D( size * sin(tempAngle) + point.x, size * cos(tempAngle) + point.y, 0.0f );
			num++;
		}
	}
}

void ippEnemyManagerClass::SetLoopWaypoints( float pointX, float pointY, bool clockwise, float angle, float size )
{
	int num = 0;
	if( clockwise )
	{
		for( double tempAngle = 0; tempAngle <= angle; tempAngle += 0.1 )
		{
			list_of_positions[num] = Vec3D( size * cos(tempAngle) + pointX, size * sin(tempAngle) + pointY, 0.0f );
			num++;
		}
	}
	else
	{
		for( double tempAngle = 0; tempAngle <= angle; tempAngle += 0.1 )
		{
			list_of_positions[num] = Vec3D( size * sin(tempAngle) + pointX, size * cos(tempAngle) + pointY, 0.0f );
			num++;
		}
	}
}

void ippEnemyManagerClass::Update()
{
	if( activateSpawner )
	{
		curTime += Global::timedelta;
		if( curTime > prevTime + 10.0f && wave_num < wave_max)	//	TIMER TO DELAY SENDING OUT SHIPS	
		{
			prevTime = curTime;
			enemyWave_.push_back( new ippEnemy( Vec3D( 500.0f, 500.0f, 0.0f ) ) );
			wave_num ++;											//	COUNTER TO KEEP TRACK OF NUMBER OF SHIPS CREATED
		}															//	SHOULD NOT RESET UNTIL ALL SHIPS DESTROYED
	}

	for( list_of_enemy::iterator enemy = enemyWave_.begin();	//	UPDATES FOR ALL SHIPS EXISITING
		enemy != enemyWave_.end(); enemy++ )
	{
		
		//	=	=	=	=	=	CODES FOR FLYING ROUND IN CIRCLES	=	=	=	=	=
		if( (*enemy)->waypoint.Reached( (*enemy)->GetPos() ) )	//	ONCE THIS SHIP HAS ARRIVED AT ITS WAYPOINT
		{
			(*enemy)->at_waypoint++;							//	CHANGE THE ARRAY NUMBER TO THE NEXT POINT
			if( (*enemy)->at_waypoint == numberOfPoints )		//	WHEN THE ARRAY HAS REACHED IT'S LAST VALUE
			{
				(*enemy)->at_waypoint = 0;
			}
			(*enemy)->MoveToWaypoint( list_of_positions[(*enemy)->at_waypoint].x, list_of_positions[(*enemy)->at_waypoint].y );
			(*enemy)->AI.SetCurrentState( (*enemy)->AI.IN_POSITION_OF_GRID );
		}
		//	=	=	=	=	=	CODES FOR FLYING ROUND IN CIRCLES	=	=	=	=	=

		(*enemy)->Update();
	}
}

void ippEnemyManagerClass::Render()
{
	for( list_of_enemy::iterator enemy = enemyWave_.begin();
		enemy != enemyWave_.end(); enemy++ )
	{
		(*enemy)->Render();
	}
}