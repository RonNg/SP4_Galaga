#include "Entities\PowerUps\PowerUpManager.h"
#include "Managers\ObjectManager.h"
#include "Entities\PowerUps\PowerUp.h"
#include <stdlib.h>
#include <time.h>

ippPowerUpManager::ippPowerUpManager(void)
{
	delay = 0.0f;
	curTime = 0.0f;
}


ippPowerUpManager::~ippPowerUpManager(void)
{
}

void ippPowerUpManager::Init ()
{
	srand (time(NULL));

	delay = 100.0f;

	powerUp = new ippPowerUp ( 20.0f, 20.0f );
	ippObjectManager::GetInstance()->AddObj( powerUp );
}

void ippPowerUpManager::Update ()
{
	if ( curTime > delay )
	{
		if ( ! ( powerUp->IsAlive () ) )
		{
			int powerType = rand () % 3 + 1;
			int x = rand () % ( Global::WIDTH_RESOLUTION - 50 ) + 50;

			switch ( powerType )
			{
			case 1:
				powerUp->SetType ( "HealthPower" );
				powerUp->SetPosition ( Vec3D ( x, 0.0f, 0.0f ) );
				powerUp->SetAlive ( true );
				break;

			case 2:
				powerUp->SetType ( "MissilePower" );
				powerUp->SetPosition ( Vec3D ( x, 0.0f, 0.0f ) );
				powerUp->SetAlive ( true );
				break;

			case 3:
				powerUp->SetType ( "SpeedPower" );
				powerUp->SetPosition ( Vec3D ( x, 0.0f, 0.0f ) );
				powerUp->SetAlive ( true );
				break;
			}

			curTime = 0.0f;
		}
	}
	else
	{
		curTime += Global::timedelta;
	}
}