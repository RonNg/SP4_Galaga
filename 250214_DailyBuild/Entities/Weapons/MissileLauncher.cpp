#include "MissileLauncher.h"
#include "Missile.h"

#include "Managers\ObjectManager.h"

ippMissileLauncher::ippMissileLauncher(void)
	:missileIndex(0)
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

void ippMissileLauncher::Init ( int numOfMissile, float turnSpeed, float speed, int damage )
{
	for ( int i = 0; i < numOfMissile; i++ )
	{
		missileList.push_back ( new ippMissile ( turnSpeed, 4.0f, 1, 10.0f, 20.0f ) );
		ippObjectManager::GetInstance()->AddObj(missileList.back());
	}
}

void ippMissileLauncher::FireMissile ( Vec3D position, Vec3D direction, Vec3D* tPosition )
{

	/*if ( missileIndex >= missileList.size() )
	{
		missileIndex = 0;
	}*/

	if ( !  ( missileList.at ( 0 )->IsAlive () ) && ! ( ( missileList.at ( 1 )->IsAlive () ) ) )
	{
		// Resets the old position of the missile
		missileList.at ( 0 )->ResetOldPosition ();
		missileList.at ( 0 )->ResetRotVal ();
	

		missileList.at ( 0 )->SetPosition ( position );
		missileList.at ( 0 )->SetDirection ( direction );
		missileList.at ( 0 )->SetMissileDir ( Vec3D ( 1.0f, 0.0f, 0.0f ) );
		missileList.at ( 0 )->SetTPosition ( tPosition );
		missileList.at ( 0 )->SetAlive ( true );
		

		// Resets the old position of the missile
		missileList.at ( 1 )->ResetOldPosition ();
		missileList.at ( 1 )->ResetRotVal ();
	

		missileList.at ( 1 )->SetPosition ( position );
		missileList.at ( 1 )->SetDirection ( direction );
		missileList.at ( 1 )->SetMissileDir ( Vec3D ( -1.0f, 0.0f, 0.0f ) );
		missileList.at ( 1 )->SetTPosition ( tPosition );
		missileList.at ( 1 )->SetAlive ( true );
	}
	/*else
	{
		++ missileIndex;
	}*/
}

void ippMissileLauncher::Update ( void )
{
	for ( int i = 0; i < missileList.size (); i++ )
	{
		if ( missileList.at ( i )->IsAlive() )
		{
			if ( !missileList.at(i)->GetPos().y <= 0 )
			{
				missileList.at ( i )->Update ();
			}
			else
			{
				missileList.at ( i )->SetAlive( false );
			}
		}
	}
}

void ippMissileLauncher::Render ( void )
{
	for ( int i = 0; i < missileList.size (); i++ )
	{
		if ( missileList.at ( i )->IsAlive() )
		{
			missileList.at ( i )->Render ();
		}
	}
}