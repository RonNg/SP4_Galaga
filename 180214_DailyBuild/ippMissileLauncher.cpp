#include "ippMissileLauncher.h"


ippMissileLauncher::ippMissileLauncher(void)
{
}


ippMissileLauncher::~ippMissileLauncher(void)
{
	for ( int i = 0; i < missileList.size (); i++)
	{
		delete missileList.at ( i );
	}

	missileList.clear ();
}

void ippMissileLauncher::FireMissile ( Vec3D position, Vec3D direction, Vec3D* tPosition )
{
	missileList.push_back ( new ippMissile ( position, tPosition, direction, 1.0f, 1, 10.0f, 10.0f ) );
}

void ippMissileLauncher::Update ( void )
{
	for ( int i = 0; i < missileList.size (); i++ )
	{
		missileList.at ( i )->Update ();

		/*if ( weaponList.at ( i )->GetPos ().x < 0 + 100 ||
			weaponList.at ( i )->GetPos ().x > Global::WIDTH_RESOLUTION - 100 ||
			weaponList.at ( i )->GetPos ().y < 0 + 100 ||
			weaponList.at ( i )->GetPos ().y < Global::HEIGHT_RESOLUTION - 100 )
		{
			delete weaponList.at ( i );
			weaponList.erase ( weaponList.begin () + i );
			size = weaponList.size ();
		}*/

	}
}

void ippMissileLauncher::Render ( void )
{
	for ( int i = 0; i < missileList.size (); i++ )
	{
		missileList.at ( i )->Render ();
	}
}