#include "Entities\PowerUps\PowerUpManager.h"
#include "Managers\ObjectManager.h"
#include "Entities\PowerUps\PowerUp.h"
#include <stdlib.h>
#include <time.h>

ippPowerUpManager::ippPowerUpManager(void)
{
	powerUpIndex = 0;
}


ippPowerUpManager::~ippPowerUpManager(void)
{
}

void ippPowerUpManager::Init ()
{
	srand (time(NULL));

	for ( int i = 0; i < 30; i++ )
	{
		powerUpList.push_back ( new ippPowerUp ( 10.0f, 10.0f ) );
		ippObjectManager::GetInstance()->AddObj(powerUpList.back());
	}
}

void ippPowerUpManager::CreateType ()
{
	if ( ! ( powerUpList.at ( powerUpIndex )->IsAlive () ) )
	{
		int powerType = rand () % 20 + 1;

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

		if ( powerUpIndex == 30 )
		{
			powerUpIndex = 0;
		}
	}
}