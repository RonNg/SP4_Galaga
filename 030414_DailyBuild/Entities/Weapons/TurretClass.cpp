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

void ippTurretClass::Init ( int numOfBullets, int speedLevel, int shotLevel )
{
	bulletIndex = 0;
	this->shotLevel = shotLevel;

	// Variables to store the value to be passed into bullet's constructor
	float speed;
	//int damage = 1;

	switch ( speedLevel )
	{
	case 1:
		speed = 20.0f;
		break;

	case 2:
		speed = 22.0f;
		break;

	case 3:
		speed = 24.0f;
		break;

	case 4:
		speed = 26.0f;
		break;

	case 5:
		speed = 28.0f;
	}

	// Starting lua
	lua_State *L = lua_open();

	// Load the libs
	luaL_openlibs(L);
	// Loading the lua file
	if(luaL_loadfile(L, "config.lua") || lua_pcall(L, 0, 0, 0))
	{
		printf("Error: &s", lua_tostring(L, -1));
	}
	
	lua_getglobal(L, "BULLETSIZEX");
	float BULLETSIZEX = (float)lua_tonumber(L, -1);

	lua_getglobal(L, "BULLETSIZEY");
	float BULLETSIZEY = (float)lua_tonumber(L, -1);



	// Adding bullets into the object manager

	for ( int i = 0; i < numOfBullets; i++ )
	{
		bulletList.push_back ( new ippBullet ( speed, BULLETSIZEX, BULLETSIZEY ) );
		ippObjectManager::GetInstance()->AddObj(bulletList.back());
	}

	lua_close(L);
}

void ippTurretClass::FireWeapon ( Vec3D position, Vec3D direction )
{

	switch ( shotLevel )
	{
	case 1:
		if ( bulletIndex > 1 )
		{
			bulletIndex = 0;
		}	

		if ( ! ( bulletList.at ( bulletIndex )->IsAlive () ) )
		{
			bulletList.at ( bulletIndex )->SetPosition ( position );
			bulletList.at ( bulletIndex )->SetDirection ( direction );
			bulletList.at ( bulletIndex )->SetAlive ( true );
			bulletIndex ++;
		}

		break;

	case 2:
		if ( bulletIndex > 3 )
		{
			bulletIndex = 0;
		}

		if ( ! ( bulletList.at ( bulletIndex )->IsAlive () ) &&
			 ! ( bulletList.at ( bulletIndex + 1 )->IsAlive () ) )
		{
			bulletList.at ( bulletIndex )->SetPosition ( Vec3D ( position.x - 10, position.y, position.z ) );
			bulletList.at ( bulletIndex )->SetDirection ( direction );
			bulletList.at ( bulletIndex )->SetAlive ( true );
			bulletIndex ++;

			bulletList.at ( bulletIndex )->SetPosition ( Vec3D ( position.x + 10, position.y, position.z ) );
			bulletList.at ( bulletIndex )->SetDirection ( direction );
			bulletList.at ( bulletIndex )->SetAlive ( true );
			bulletIndex ++;
		}
		break;

		case 3:
		if ( bulletIndex > 5 )
		{
			bulletIndex = 0;
		}

		if ( ! ( bulletList.at ( bulletIndex )->IsAlive () ) &&
			 ! ( bulletList.at ( bulletIndex + 1 )->IsAlive () ) &&
			 ! ( bulletList.at ( bulletIndex + 2 )->IsAlive () ) )
		{
			bulletList.at ( bulletIndex )->SetPosition ( Vec3D ( position.x, position.y, position.z ) );
			bulletList.at ( bulletIndex )->SetDirection ( direction );
			bulletList.at ( bulletIndex )->SetAlive ( true );
			bulletIndex ++;

			bulletList.at ( bulletIndex )->SetPosition ( Vec3D ( position.x - 10, position.y, position.z ) );
			bulletList.at ( bulletIndex )->SetDirection ( Vec3D ( direction.x - 0.15, direction.y, direction.z ) );
			bulletList.at ( bulletIndex )->SetAlive ( true );
			bulletIndex ++;

			bulletList.at ( bulletIndex )->SetPosition ( Vec3D ( position.x + 10, position.y, position.z ) );
			bulletList.at ( bulletIndex )->SetDirection ( Vec3D ( direction.x + 0.15, direction.y, direction.z ) );
			bulletList.at ( bulletIndex )->SetAlive ( true );
			bulletIndex ++;
		}
		break;
	}
	
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