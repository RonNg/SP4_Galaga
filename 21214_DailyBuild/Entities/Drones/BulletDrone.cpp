#include "BulletDrone.h"
#include "Managers\ObjectManager.h"


ippBulletDrone::ippBulletDrone(void)
{
}


ippBulletDrone::~ippBulletDrone(void)
{
}

void ippBulletDrone::Init ( void )
{
	ippObjectManager::GetInstance ()->AddObj ( bullet );
}

void ippBulletDrone::Update ( void )
{
	curTime += Global::timedelta;
	if ( delay < curTime )
	{
		bullet->SetAlive ( true );
		bullet->SetDirection ( Vec3D ( 1.0f, -1.0f, 0.0f ) );

		curTime = 0.0f;
	}
}