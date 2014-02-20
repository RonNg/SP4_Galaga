#include "EnemyManager.h"


ippEnemyManager::ippEnemyManager(void)
:	numberOfPoints(99)
,	waypointTracker(0)
,	curTime(0.0f)
,	prevTime(0.0f)
,	diffTime(0.0f)
,	wave_num(0)
,	current_state(0)
,	pie(3.141592654)
,	tenDegrees(0.17453292522222222222222222222222)
,	activateSpawner(true)
{
	srand(time(NULL));
}

ippEnemyManager::~ippEnemyManager(void)
{
	if( list_of_positions != NULL )
	{
		delete [] list_of_positions;
	}
	if( theGrid != NULL )
	{
		delete theGrid;
	}
	enemyWave_.clear();
}

void ippEnemyManager::Init( int numberOfEnemies )
{
	int value = 2 * pie * 10;
	list_of_positions = new Vec3D[ numberOfPoints ];					//	CREATING ARRAY BASED ON SIZE OF TURNING POINT
	wave_max = numberOfEnemies;											//	LIMIT THE NUMBER OF ENEMY SHIPS SPAWN IN ONE WAVE
	int num = 0;

	theGrid = new ippEnemyGrid();
	theGrid->Init( 200.0f, 200.0f, 5, 5, 20.0f, 20.0f );
	theGrid->SetGridposition( Vec3D( 400.0f, 300.0f, 0.0f ) );
	
	ResetWaypointsAt( 400.0f, 300.0f );
	AddLoop( 200.0f, 300.0f, false, 0, 63, 20, 100.0f );
	AddWaypoint( 500.0f, 300.0f, 63 );
	//ShowWaypoints();
	//	=	=	=	=	=	THIS CODE IS FOR DEBUGGING VALUES	=	=	=	=	=
	//for( int i = 0; i < numberOfPoints; i++ )							//	THIS CODE WAS THE ORIGINAL CIRCLE CODES
	//{
	//	float angle = -i;
	//	list_of_positions[i] = Vec3D( 100 * cos(angle)+400, 100 * sin(angle)+300, 0.0f );
	//}
	//	=	=	=	=	=	THIS CODE IS FOR DEBUGGING VALUES	=	=	=	=	=
}

void ippEnemyManager::CreateWaves( int number_of_ships, int enemy_type )
{
	for( int counter = 0; counter < number_of_ships; counter++ )
	{
		Vec3D tempPos = Vec3D( rand()%200+300, rand()%200+200, 0.0f );
		enemyWave_.push_back( new ippEnemy( tempPos ) );
		enemyWave_.at( counter )->MoveToWaypoint( list_of_positions[counter].x, list_of_positions[counter].y );
	}
}

void ippEnemyManager::ActivateSpawn()
{
	activateSpawner = true;
}

void ippEnemyManager::Spawner( int number_of_ships, int enemy_type, Vec3D spawnpoint, Vec3D flyThere, float interval )
{
	wave_max = number_of_ships;
	spawnerPos = spawnpoint;
	firstWaypoint = flyThere;
	diffTime = interval;
	activateSpawner = true;
}

void ippEnemyManager::Spawner( int number_of_ships, int enemy_type, float spawnX, float spawnY, float flyX, float flyY, float interval )
{
	wave_max = number_of_ships;
	spawnerPos = Vec3D( spawnX, spawnY, 0.0f );
	firstWaypoint = Vec3D( flyX, flyY, 0.0f );
	diffTime = interval;
	activateSpawner = true;
}

void ippEnemyManager::AddWaypoint( Vec3D point, int tracker )
{
	list_of_positions[tracker] = point;
}

void ippEnemyManager::AddWaypoint( float pointX, float pointY, int tracker )
{
	list_of_positions[tracker] = Vec3D( pointX, pointY, 0.0f );
}

void ippEnemyManager::AddLoop( Vec3D point, bool clockwise, int tracker, int stopHere, int angleBreak, float size, float angle )
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
	int num = tracker;
	if( clockwise )
	{
		for( double tempAngle = angleBreak; tempAngle <= angle + angleBreak; tempAngle += 0.1 )		//	CREATE WAYPOINTS BASED ON CIRCLE FORMULA
		{
			if( num >= stopHere )
			{
				break;
			}
			list_of_positions[num] = Vec3D( size * cos(tempAngle) + point.x, size * sin(tempAngle) + point.y, 0.0f );
			num++;
		}
	}
	else
	{
		for( double tempAngle = angle + angleBreak; tempAngle >= angleBreak; tempAngle -= 0.1 )
		{
			if( num >= stopHere )
			{
				break;
			}
			list_of_positions[num] = Vec3D( size * cos(tempAngle) + point.x, size * sin(tempAngle) + point.y, 0.0f );
			num++;
		}
	}
}

void ippEnemyManager::AddLoop( float pointX, float pointY, bool clockwise, int tracker, int stopHere, int angleBreak, float size, float angle )
{
	int num = tracker;
	if( clockwise )
	{
		for( double tempAngle = angleBreak; tempAngle <= angle + angleBreak; tempAngle += 0.1 )
		{
			if( num >= stopHere )
			{
				break;
			}
			list_of_positions[num] = Vec3D( size * cos(tempAngle) + pointX, size * sin(tempAngle) + pointY, 0.0f );
			num++;
		}
	}
	else
	{
		for( double tempAngle = angle + angleBreak; tempAngle >= angleBreak; tempAngle -= 0.1 )
		{
			if( num >= stopHere )
			{
				break;
			}
			list_of_positions[num] = Vec3D( size * cos(tempAngle) + pointX, size * sin(tempAngle) + pointY, 0.0f );
			num++;
		}
	}
}

void ippEnemyManager::ClearWaypoints()
{
	for( int counter = 0; counter < numberOfPoints; counter++ )
	{
		list_of_positions[ counter ] = Vec3D(0,0,0);
	}
}

void ippEnemyManager::ResetWaypointsAt( Vec3D point )
{
	for( int counter = 0; counter < numberOfPoints; counter++ )
	{
		list_of_positions[ counter ] = point;
	}
}

void ippEnemyManager::ResetWaypointsAt( float pointX, float pointY )
{
	for( int counter = 0; counter < numberOfPoints; counter++ )
	{
		list_of_positions[ counter ] = Vec3D( pointX, pointY, 0.0f );
	}
}

void ippEnemyManager::ShowWaypoints()
{
	for( int counter = 0; counter < numberOfPoints; counter ++ )
	{
		printf( "%d -->> %3.3f, %3.3f,\n", counter, list_of_positions[ counter ].x, list_of_positions[ counter ].y );
	}
}

void ippEnemyManager::Update()
{
	if( activateSpawner )
	{
		curTime += Global::timedelta;
		if( curTime > prevTime + diffTime )							//	TIMER TO DELAY SENDING OUT SHIPS	
		{
			prevTime = curTime;
			enemyWave_.push_back( new ippEnemy( spawnerPos ) );
			enemyWave_.at(wave_num)->StateMove();
			enemyWave_.at(wave_num)->MoveToWaypoint( firstWaypoint );
			printf( "spawned %d at %3.3f\n", wave_num, curTime );
			wave_num ++;											//	COUNTER TO KEEP TRACK OF NUMBER OF SHIPS CREATED
		}															//	SHOULD NOT RESET UNTIL ALL SHIPS DESTROYED
		if( wave_num >= wave_max )
		{
			activateSpawner = false;
		}
	}

	for( list_of_enemy::iterator enemy = enemyWave_.begin();	//	UPDATES FOR ALL SHIPS EXISITING
		enemy != enemyWave_.end(); enemy++ )
	{
		
		if( (*enemy)->GetState() == (*enemy)->ON_THE_MOVE )
		{
			//	=	=	=	=	=	CODES FOR FLYING ROUND IN CIRCLES	=	=	=	=	=
			if( (*enemy)->waypoint.Reached( (*enemy)->GetPos() ) )	//	ONCE THIS SHIP HAS ARRIVED AT ITS WAYPOINT
			{
				(*enemy)->at_waypoint++;							//	CHANGE THE ARRAY NUMBER TO THE NEXT POINT
				if( (*enemy)->at_waypoint == numberOfPoints )		//	WHEN THE ARRAY HAS REACHED IT'S LAST VALUE
				{
					(*enemy)->StateFloat();
					break;
				}
				(*enemy)->MoveToWaypoint( list_of_positions[(*enemy)->at_waypoint] );
				(*enemy)->AI.SetCurrentState( (*enemy)->AI.IN_POSITION_OF_GRID );
			}
			//	=	=	=	=	=	CODES FOR FLYING ROUND IN CIRCLES	=	=	=	=	=
		}

		(*enemy)->Update();
	}
}

void ippEnemyManager::Render()
{
	theGrid->Render();

	for( list_of_enemy::iterator enemy = enemyWave_.begin();
		enemy != enemyWave_.end(); enemy++ )
	{
		(*enemy)->Render();
	}
}