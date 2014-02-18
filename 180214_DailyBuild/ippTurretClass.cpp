#include "ippTurretClass.h"


ippTurretClass::ippTurretClass(void)
{
}


ippTurretClass::~ippTurretClass(void)
{
	for ( int i = 0; i < bulletList.size (); i++)
	{
		delete bulletList.at ( i );
	}

	bulletList.clear ();
}

void ippTurretClass::FireWeapon ( Vec3D position, Vec3D direction )
{
	bulletList.push_back ( new ippBulletClass ( position, direction, 1.0f, 1, 10.0f, 10.0f ) );
}

void ippTurretClass::Update ( void )
{
	for ( int i = 0; i < bulletList.size (); i++ )
	{
		bulletList.at ( i )->Update ();

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

void ippTurretClass::Render ( void )
{
	for ( int i = 0; i < bulletList.size (); i++ )
	{
		bulletList.at ( i )->Render ();
	}
}