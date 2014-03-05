#include "Entities\PowerUps\PowerUpManager.h"
#include "Managers\ObjectManager.h"
#include "Entities\PowerUps\PowerUp.h"
#include <stdlib.h>
#include <time.h>

ippPowerUpManager::ippPowerUpManager(void)
{
	delay = 0.0f;
	curTime = 0.0f;
	powerUpIndex = 0;
}


ippPowerUpManager::~ippPowerUpManager(void)
{
}

void ippPowerUpManager::Init ()
{
	srand (time(NULL));

	delay = 100.0f;

	for ( int i = 0; i < 30; i++ )
	{
		powerUpList.push_back ( new ippPowerUp ( 10.0f, 10.0f ) );
		ippObjectManager::GetInstance()->AddObj(powerUpList.back());
	}
}

void ippPowerUpManager::Update ()
{
	if ( curTime > delay )
	{
		if ( ! ( powerUpList.at ( powerUpIndex )->IsAlive () ) )
		{
			int powerType = rand () % 3;

			switch ( powerType )
			{
			case 1:
				powerUpList.at ( powerUpIndex )->SetType ( "HealthPower" );
				powerUpList.at ( powerUpIndex )->SetAlive ( true );
				powerUpIndex ++;
				break;

			case 2:
				powerUpList.at ( powerUpIndex )->SetType ( "MissilePower" );
				powerUpList.at ( powerUpIndex )->SetAlive ( true );
				powerUpIndex ++;
				break;

			case 3:
				powerUpList.at ( powerUpIndex )->SetType ( "SpeedPower" );
				powerUpList.at ( powerUpIndex )->SetAlive ( true );
				powerUpIndex ++;
				break;
			}

			curTime = 0.0f;

			if ( powerUpIndex > 29 )
			{
				powerUpIndex = 0;
			}
		}
	}
	else
	{
		curTime += Global::timedelta;
	}
}