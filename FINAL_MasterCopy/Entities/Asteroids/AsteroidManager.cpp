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
	srand ( ( unsigned int ) time(NULL));

	delay = ( float ) ( rand () % 10 + 15 );

	for ( int i = 0; i < 1; i++ )
	{
		asteroidList.push_back ( new ippAsteroid () );
		ippObjectManager::GetInstance()->AddObj(asteroidList.back());
	}
}

void ippAsteroidManager::Update ( void )
{
}