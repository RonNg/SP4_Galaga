#include "Entities\Asteroids\AsteroidManager.h"
#include "Entities\Asteroids\Asteroid.h"
#include "Managers\ObjectManager.h"
#include <stdlib.h>
#include <time.h>


ippAsteroidManager::ippAsteroidManager(void)
{
	delay = 0.0f;
	curTime = 0.0f;
	asteroidIndex = 0;
}


ippAsteroidManager::~ippAsteroidManager(void)
{
}

void ippAsteroidManager::Init ( void )
{
	srand (time(NULL));

	delay = rand () % 10 + 15;

	for ( int i = 0; i < 30; i++ )
	{
		asteroidList.push_back ( new ippAsteroid () );
		ippObjectManager::GetInstance()->AddObj(asteroidList.back());
	}
}

void ippAsteroidManager::Update ( void )
{
	// Random the spawn point on the x-axis
	float x = rand () % ( Global::WIDTH_RESOLUTION - 50 ) + 50;
	float rotSpeed = rand () % 5 + 1;
	float speed = rand () % 10 + 5;
	float size = rand () % 20 + 5;

	if ( curTime > delay )
	{
		asteroidList.at ( asteroidIndex )->SetAlive ( true );
		asteroidList.at ( asteroidIndex )->SetPosition ( Vec3D ( x, 0.0f, 0.0f ) );
		asteroidList.at ( asteroidIndex )->SetRotSpeed ( rotSpeed );
		asteroidList.at ( asteroidIndex )->SetSpeed ( speed );
		asteroidList.at ( asteroidIndex )->SetSize ( size, size );

		// Resets the timer
		curTime = 0.0f;
		delay = rand () % 10 + 15;	// Reset the delay to another random value
		asteroidIndex ++;
	}
	else
	{
		curTime += Global::timedelta;
	}

	if ( asteroidIndex > 29 )
		{
			asteroidIndex = 0;
		}
}