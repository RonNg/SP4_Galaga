#include "TurretClass.h"
#include "Bullet.h"

#include "Managers\ObjectManager.h"

#include "Globals.h"
using namespace Global;



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

void ippTurretClass::Init ( int numOfBullets )
{
	for ( int i = 0; i < numOfBullets; i++ )
	{
		bulletList.push_back ( new ippBullet ( 15.0f, 1, 2.5f, 2.5f ) );
		ippObjectManager::GetInstance()->AddObj(bulletList.back());
	}
}

void ippTurretClass::FireWeapon ( Vec3D position, Vec3D direction )
{
	if ( bulletIndex >= bulletList.size() )
	{
		bulletIndex = 0;
	}

	bulletList.at ( bulletIndex )->SetPosition ( position );
	bulletList.at ( bulletIndex )->SetDirection ( direction );
	bulletList.at ( bulletIndex )->SetAlive ( true );

	++ bulletIndex;
}

//void ippTurretClass::Update ( void )
//{
//	for ( int i = 0; i < bulletList.size (); i++ )
//	{
//		if ( bulletList.at ( i )->IsAlive() )
//		{
//
//			// If the bullet hit near the edge of the screen, derender it
//			if ( bulletList.at ( i )->GetPos ().x < 0 + 100 ||
//				bulletList.at ( i )->GetPos ().x > Global::WIDTH_RESOLUTION - 100 ||
//				bulletList.at ( i )->GetPos ().y < 0 + 100 /*||
//				bulletList.at ( i )->GetPos ().y < Global::HEIGHT_RESOLUTION - 100*/ )
//			{
//				bulletList.at ( i )->SetAlive ( false );
//			}
//
//			else
//			{
//				//bulletList.at ( i )->Update ();
//			}
//		}
//	}
//}
//
//void ippTurretClass::Render ( void )
//{
//	for ( int i = 0; i < bulletList.size (); i++ )
//	{
//		if ( bulletList.at ( i )->IsAlive() )
//		{
//			bulletList.at ( i )->Render ();
//		}
//	}
//}