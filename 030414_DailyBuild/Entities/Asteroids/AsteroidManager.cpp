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

	for ( int i = 0; i < 1; i++ )
	{
		asteroidList.push_back ( new ippAsteroid () );
		ippObjectManager::GetInstance()->AddObj(asteroidList.back());
	}
}

void ippAsteroidManager::Update ( void )
{
	cout << "  ASTEROID UPDATE " << endl;

	if ( curTime > delay )
	{
		bool side = rand () % 2;	// This randomize which side it spawns from
		float x;

		// Random the side where it spawn from
		if ( side == 0 )
		{
			x = 0;
			asteroidList.at ( asteroidIndex )->SetDirection ( Vec3D ( 1.0f, 0.0f, 0.0f ) );
		}
		else
		{
			x = Global::WIDTH_RESOLUTION;
			asteroidList.at ( asteroidIndex )->SetDirection ( Vec3D ( -1.0f, 0.0f, 0.0f ) );
		}

		float y	= rand () % ( Global::HEIGHT_RESOLUTION / 3 ) + ( Global::HEIGHT_RESOLUTION / 3 );

		float rotSpeed = rand () % 5 + 1;
		float speed = rand () % 10 + 5;
		float size = rand () % 10 + 5;

		asteroidList.at ( asteroidIndex )->SetAlive ( true );
		asteroidList.at ( asteroidIndex )->SetPosition ( Vec3D ( x, y, 0.0f ) );
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

	if ( asteroidIndex > 0 )
	{
		asteroidIndex = 0;
	}
}