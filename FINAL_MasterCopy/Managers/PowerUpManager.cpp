#include "Managers\PowerUpManager.h"
#include "Managers\ObjectManager.h"
#include "Entities\PowerUps\PowerUp.h"
#include <stdlib.h>
#include <time.h>

ippPowerUpManager::ippPowerUpManager(void)
{
	delay = 0.0f;
	curTime = 0.0f;
	prevTime = 0.0f;
}


ippPowerUpManager::~ippPowerUpManager(void)
{
}

void ippPowerUpManager::Init ()
{
	srand (time(NULL));

	delay = 10 * 1000.0f;

	powerUp = new ippPowerUp ( 30.0f, 30.0f );
	ippObjectManager::GetInstance()->AddObj( powerUp );
}

void ippPowerUpManager::Update ()
{
	curTime = glutGet ( GLUT_ELAPSED_TIME );

	if ( ( curTime - prevTime ) > delay )
	{
		if ( ! ( powerUp->IsAlive () ) )
		{
			int powerType = rand () % 2 + 1;
			int x = rand () % ( (int) Global::WIDTH_RESOLUTION - 50 ) + 50;

			switch ( powerType )
			{
			case 1:
				powerUp->SetType ( "MissilePower" );
				powerUp->SetPosition ( Vec3D ( x, 0.0f, 0.0f ) );
				powerUp->SetAlive ( true );
				break;

			case 2:
				powerUp->SetType ( "SpeedPower" );
				powerUp->SetPosition ( Vec3D ( x, 0.0f, 0.0f ) );
				powerUp->SetAlive ( true );
				break;
			}

			prevTime = curTime;
		}
	}
}