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

void ippMissileLauncher::Init ( int numOfMissile )
{
	for ( int i = 0; i < numOfMissile; i++ )
	{
		missileList.push_back ( new ippMissile ( 300.0f, 1, 5.0f, 5.0f ) );
		ippObjectManager::GetInstance()->AddObj(missileList.back());
	}
}

void ippMissileLauncher::FireMissile ( Vec3D position, Vec3D direction, Vec3D* tPosition )
{

	if ( missileIndex >= missileList.size() )
	{
		missileIndex = 0;
	}

	// Resets the old position of the missile
	missileList.at ( missileIndex )->ResetOldPosition ();
	missileList.at ( missileIndex )->ResetRotVal ();
	

	missileList.at ( missileIndex )->SetPosition ( position );
	missileList.at ( missileIndex )->SetDirection ( direction );
	missileList.at ( missileIndex )->SetTPosition ( tPosition );
	missileList.at ( missileIndex )->SetAlive ( true );

	++ missileIndex;
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