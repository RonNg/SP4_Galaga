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

void ippMissileLauncher::Init ( int numOfMissile, int turnSpeedLevel, int speedLevel, int damageLevel )
{
	float turnSpeed;
	float speed;
	int damage = 1;

	// Converting the levels into actual values
	
	switch ( turnSpeedLevel )
	{
	case 1:
		turnSpeed = 2.0f;
		break;
		
	case 2:
		turnSpeed = 2.5f;
		break;

	case 3:
		turnSpeed = 3.0f;
		break;

	case 4:
		turnSpeed = 3.5f;
		break;

	case 5:
		turnSpeed = 4.0f;
		break;
	}

	switch ( speedLevel )
	{
	case 1:
		speed = 5.0f;
		break;
		
	case 2:
		speed = 7.0f;
		break;

	case 3:
		speed = 9.0f;
		break;

	case 4:
		speed = 11.0f;
		break;

	case 5:
		speed = 13.0f;
		break;
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
	
	lua_getglobal(L, "MISSILESIZEX");
	float MISSILESIZEX = (float)lua_tonumber(L, -1);

	lua_getglobal(L, "MISSILESIZEY");
	float MISSILESIZEY = (float)lua_tonumber(L, -1);


	for ( int i = 0; i < numOfMissile; i++ )
	{
		missileList.push_back ( new ippMissile ( turnSpeed, 4.0f, 1, MISSILESIZEX, MISSILESIZEY ) );
		ippObjectManager::GetInstance()->AddObj(missileList.back());
	}

	lua_close(L);
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