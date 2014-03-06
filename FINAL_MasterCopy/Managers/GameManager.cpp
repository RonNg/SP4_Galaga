#include "GameManager.h"

#include "Globals.h"
using namespace Global;


#include "Managers\ObjectManager.h"
#include "Managers\CollisionManager.h"
#include "Managers\EmitterManager.h"
#include "Managers\PowerUpManager.h"

#include "SaveGame\SaveManager.h"
#include "Systems\EnemySpawner.h"
#include "Systems\EnemyGrid.h"

#include "Entities\AI\Enemy.h"
#include "Entities\Weapons\Bullet.h"
#include "Entities\Ship\Ship.h"
#include "Entities\PowerUps\PowerUp.h"
#include "StarBackground\Star.h"
#include "StarBackground\StarManager.h"

#include "GameUI\GameUI.h"

ippGameManager::ippGameManager(void)
	: waveNo (1)
	, loadFinish ( false )
	, bulletIndex ( 0 )
	, bufferSize ( 10 )
	, enableShoot ( false )
	, startGame ( false )
	, highscore ( 0 )
	, waveDisplay ( true )
{
	gameState = gameState_t::SPLASH;
	theGrid = new ippEnemyGrid();

	BuildFont();

	prevTime =  (float) glutGet ( GLUT_ELAPSED_TIME );
	attackPrevTime = (float) glutGet ( GLUT_ELAPSED_TIME );
	prevDisplay = (float) glutGet ( GLUT_ELAPSED_TIME );
}

ippGameManager::~ippGameManager(void)
{
	KillFont();
}

void ippGameManager::Init ()
{
	//Inits particles for enemy explosms
	ippEmitterManager::GetInstance()->Init(10,100);

	powerupManager = new ippPowerUpManager ();
	powerupManager->Init ();

	starManager = new ippStarManager ();
	starManager->Init ();

	Init_GameUI();
	Init_Enemies();
	Init_SaveManager();
}
void ippGameManager::Init_Enemies ()
{
	
	for ( int i = 0; i < bufferSize; i++ )
	{
		enemyBulletList.push_back ( new ippBullet ( 10.0f, 5.0f, 10.0f, "Enemy Bullet") );
	}

	greenPool = 4;
	redPool = 16;
	bluePool = 20;

	spawnerList.push_back(new ippEnemySpawner ( -100, Global::HEIGHT_RESOLUTION - 100, theGrid, 1 ) );
	spawnerList.push_back(new ippEnemySpawner ( Global::WIDTH_RESOLUTION + 100, Global::HEIGHT_RESOLUTION - 100 , theGrid, 2 ) );

	spawnerList.push_back(new ippEnemySpawner ( 100, -100, theGrid, 3 ) );
	spawnerList.push_back(new ippEnemySpawner ( Global::WIDTH_RESOLUTION - 100, -100, theGrid, 4 ) );

	spawnerList.push_back(new ippEnemySpawner ( -100, Global::HEIGHT_RESOLUTION/2, theGrid, 5 ) );
	spawnerList.push_back(new ippEnemySpawner ( Global::WIDTH_RESOLUTION + 100, Global::HEIGHT_RESOLUTION/2, theGrid, 6 ) );

}
void ippGameManager::Init_GameUI ()
{
	theGameUI = new GameUI ();
	theGameUI->AddMenu("Splash","Images/SplashScreen.tga");

	theGameUI->AddMenu("Main Menu","Images/Background.tga");

	theGameUI->AddButton("Start",Global::WIDTH_RESOLUTION/2,450);
	theGameUI->AddButton("Shop",Global::WIDTH_RESOLUTION/2, 500);
	theGameUI->AddButton("Quit", Global::WIDTH_RESOLUTION/2, 550);

	theGameUI->AddMenu("Game Start","Images/GameScreen.tga");

	// Insert Game Screen here

	theGameUI->AddMenu("Shop","Images/ShopScreen.tga");
	theGameUI->AddButton("ShipSpeed",400,50);
	theGameUI->AddButton("ShipEvasion",400,100);
	theGameUI->AddButton("BulletSpeed",400,150);
	theGameUI->AddButton("BulletLevel",400,200);
	theGameUI->AddButton("MissileSpeed",400,250);
	theGameUI->AddButton("MissileTurnSpeed",400,300);
	theGameUI->AddButton("DroneFireRate",400,350);
	theGameUI->AddButton("Back",400,400);
	
	
	theGameUI->AddMenu("Game Over","Images/GG.tga");

	theGameUI->Move("Splash");

}
void ippGameManager::Init_SaveManager ()
{
	/*
	===========================================
	Init the save file
	===========================================
	*/
	if ( ! ( ippSaveManager::GetInstance()->Init( "GameUpgrades.txt" ) ) )
	{
		// Adding all the catagories
		ippSaveManager::GetInstance ()->AddCategory ( "BULLETSPEED" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "1", "BULLETSPEED" );

		ippSaveManager::GetInstance ()->AddCategory ( "BULLETLEVEL" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "2", "BULLETLEVEL" );

		ippSaveManager::GetInstance ()->AddCategory ( "MISSILESPEED" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "1", "MISSILESPEED" );

		ippSaveManager::GetInstance ()->AddCategory ( "MISSILETURNSPEED" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "5", "MISSILETURNSPEED" );

		ippSaveManager::GetInstance ()->AddCategory ( "SHIPSPEED" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "1", "SHIPSPEED" );

		ippSaveManager::GetInstance ()->AddCategory ( "SHIPEVASION" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "1", "SHIPEVASION" );

		ippSaveManager::GetInstance ()->AddCategory ( "DRONERATE" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "1", "DRONERATE" );
	}

	/*
	===========================================
	Init the save file
	===========================================
	*/
	// Starting lua
	lua_State *L = lua_open();

	// Load the libs
	luaL_openlibs(L);
	// Loading the lua file
	if(luaL_loadfile(L, "config.lua") || lua_pcall(L, 0, 0, 0))
	{
		printf("Error: &s", lua_tostring(L, -1));
	}
	
	lua_getglobal(L, "SHIPSIZEX");
	float SHIPSIZEX = (float)lua_tonumber(L, -1);

	lua_getglobal(L, "SHIPSIZEY");
	float SHIPSIZEY = (float)lua_tonumber(L, -1);
	
	// Getting the levels from the save file
	int shipSpeed = ippSaveManager::GetInstance ()->GetInt ( "SHIPSPEED" );
	int shipEvasion = ippSaveManager::GetInstance ()->GetInt ( "SHIPEVASION " );

	playerShip = new ippShip (Global::WIDTH_RESOLUTION/2, Global::HEIGHT_RESOLUTION - 25, 0.0f, SHIPSIZEX, SHIPSIZEY );
	playerShip->Init( shipSpeed, shipEvasion );

	lua_close(L);
}
void ippGameManager::Update ()
{
	IO_Handler();

	if ( pauseGame == false )
	{
		ippEmitterManager::GetInstance()->Update();
		switch ( gameState )
		{
		case PLAY:
			Update_Game();
			break;
		case MENU:
			Update_Menu();
			break;
		case GAME_OVER:
			WipeEnemyFromExistence();		

			for ( int i = enemyBulletList.size() - 1; i >= 0; -- i )
			{
				enemyBulletList.at ( i )->SetAlive ( false );
			}
			theGameUI->Move("Game Over");

			Update_Menu();
			break;
		case SPLASH:
			theGameUI->MoveWithTransition("Splash");
			Update_Menu();
			break;
		case SHOP:
			Update_Menu();
			break;
		}
	}
}
void ippGameManager::Update_Game ()
{
	if ( playerShip->IsAlive() == false )
	{
		gameState = GAME_OVER;
		waveDisplay = false;
		return;
	}

	if ( !loadFinish )
	{
		LoadLevel();
		loadFinish = true;
		
		waveDisplay = true;
	}

		float displayNow = glutGet ( GLUT_ELAPSED_TIME );

		if ( ( displayNow- prevDisplay ) > 3.0f * 1000.0f )
		{
			if ( waveDisplay )
			{
				waveDisplay = false;
			}

			prevDisplay = displayNow;
		}

	
	theGrid->Update();
	powerupManager->Update();
	starManager->Update();
	Spawn();
	DeleteFlagged();

	totalNo = ippObjectManager::GetInstance()->GetNumberOfEnemy();

	float now = glutGet ( GLUT_ELAPSED_TIME );
	//Delays checking to every 3 seconds
	if ( ( now - prevTime ) > 3 * 1000.0f ) 
	{
		//Check if all enemies eliminated
		if ( totalNo <= 0 )
		{
			waveNo ++;
			Reset();
		}
		prevTime = now;
	}
}
void ippGameManager::Update_Menu ()
{
	if (theGameUI->page() == "Splash")
	{
		if(Global::start == true || GetAsyncKeyState ( VK_RETURN ) )
		{
			theGameUI->Move("Main Menu");	
			gameState = MENU;
			theSoundEngine->stopAllSounds();
			Global::start = false;
		}
	}
	else if (theGameUI->page() == "Main Menu")
	{
		if ( command == "Start" ||  GetAsyncKeyState ( VK_RETURN ) )
		{
			//theGameUI->Move("Game Start");
			Sound_ThemeSong = theSoundEngine->play2D("Sounds/Level_Start.mp3",false);
			gameState = PLAY;
			
			Global::JoystickA = false;
			return;

		}
		else if (command == "Shop")
		{
			theGameUI->Move ("Shop");
			gameState = SHOP;
		}
		else if  (command == "Quit")
		{
			glutLeaveMainLoop();
		}
		command = 0;
	}
	else if ( theGameUI->page() == "Game Over")
	{
		if ( Global::start || GetAsyncKeyState ( VK_RETURN ) )
		{
			theGameUI->Move( "Main Menu" );
			gameState = MENU;
			
			glColor3f(1,1,1);
			glRasterPos2f(360,57);
			glPrint("Press [Start] to return to Main Menu!");

			Reset_Game();
			playerShip->SetAlive ( true );
			Global::start = false;
		}
	}
	else if ( theGameUI->page() == "Shop")
	{
	if ( command == "ShipSpeed" )
		{
			if ( shipSpeed < 5 )
			{
				shipSpeed += 1;
			}
			else
			{
				// Error msg
			}
		}

		else if ( command == "ShipEvasion" )
		{
			if ( shipEvasion < 5 )
			{
				shipEvasion += 1;
			}
			else
			{
				// Error msg
			}
		}

		else if ( command == "BulletSpeed" )
		{
			if ( bulletSpeed < 5 )
			{
				bulletSpeed += 1;
			}
			else
			{
				// Error msg
			}
		}

		else if ( command == "BulletLevel" )
		{
			if ( bulletLevel < 5 )
			{
				bulletLevel += 1;
			}
			else
			{
				// Error msg
			}
		}

		else if ( command == "MissileSpeed" )
		{
			if ( missileSpeed < 5 )
			{
				missileSpeed += 1;
			}
			else
			{
				// Error msg
			}
		}

		else if ( command == "MissileTurnSpeed" )
		{
			if ( missileTurnSpeed < 5 )
			{
				missileTurnSpeed += 1;
			}
			else
			{
				// Error msg
			}
		}

		else if ( command == "DroneFireRate" )
		{
			if ( droneFireRate > 5 )
			{
				droneFireRate += 1;
			}
			else
			{
				// Error msg
			}
		
		}
		else if(command == "Back")
		{
			gameState = MENU;
			/*ippSaveManager::GetInstance ()->EditThis ( "SHIPSPEED",shipSpeed );
			ippSaveManager::GetInstance ()->EditThis ( "SHIPEVASION",shipEvasion );
			ippSaveManager::GetInstance ()->EditThis ( "BULLETSPEED",bulletSpeed );
			ippSaveManager::GetInstance ()->EditThis ( "BULLETLEVEL",bulletLevel );
			ippSaveManager::GetInstance ()->EditThis ( "MISSILESPEED",missileSpeed );
			ippSaveManager::GetInstance ()->EditThis ( "MISSILETURNSPEED",missileTurnSpeed );
			ippSaveManager::GetInstance ()->EditThis( "DRONERATE",droneFireRate );*/

			theGameUI->Move("Main Menu");
		}
		command = 0;
	}
}
void ippGameManager::Render ()
{

	ippEmitterManager::GetInstance()->Render();
	starManager->Render ();

	if ( Global::pauseGame )
	{
		glColor3f(1,1,1);
		glRasterPos2f(200,300);
		glPrint( " Game is Paused. Press Start to resume." );
		return;
	}

	if ( waveDisplay )
	{
		glColor3f(1,1,1);
		glRasterPos2f(325,300);
		glPrint( "Prepare for Wave  %d", waveNo );
	}

	switch ( gameState )
	{
	case SPLASH:
		theGameUI->Render();
		theGameUI->RenderSplashText();
		break;
	case MENU:
		theGameUI->Render();
		theGameUI->RenderMainMenuText();
		break;
	case SHOP:
		theGameUI->Render();
		theGameUI->RenderShopText();
		break;
	case GAME_OVER:
		theGameUI->Render();
		glColor3f(1,1,1);
		glRasterPos2f(200,525);
		glPrint( "Press [Start] to Return to Main Menu " );
		break;
	case PLAY:
		glColor3f(1,1,1);
		glRasterPos2f(500, 50);
		glPrint( "High Score:     %d", highscore );
		break;
	}
}
void ippGameManager::Reset ()
{
	for ( int i = 0; i < (int)spawnerList.size(); i ++ )
	{
		spawnerList[i]->Reset();
	}
	loadFinish = false;

	theGrid->ResetGrid();

	greenPool = 4;
	redPool = 16;
	bluePool = 20;

}
void ippGameManager::Reset_Game ()
{
	playerShip->SetAlive ( true );
	waveDisplay = false;
	highscore = 0;
	waveNo = 0;
}
void ippGameManager::Spawn()
{
	for ( int i = 0; i < (int)spawnerList.size(); ++ i )
	{
		spawnerList[i]->Spawn();
	}
}
void ippGameManager::IO_Handler ()
{
	
	if( gameState == PLAY && Global::start == true || GetAsyncKeyState ( VK_RETURN ) )
	{
		Global::start = false;
		Global::pauseGame = !Global::pauseGame;
	}

	if ( Global::pauseGame == false )
	{
		// Joystick Left
		if(Global::JoystickLeft == true || GetAsyncKeyState(VK_LEFT) )
		{
			playerShip->Movement(ippShip::LEFT);
		}
		// Joystick Right
		if(Global::JoystickRight == true || GetAsyncKeyState(VK_RIGHT))
		{
			playerShip->Movement(ippShip::RIGHT);
		}
		// Joystick Up	
		if(	Global::JoystickUp == true || GetAsyncKeyState ( VK_UP ) )
		{
			theGameUI->Update(true);
			Global::JoystickUp = false;
		}
		// Joystick Down
		else if ( Global::JoystickDown == true || GetAsyncKeyState ( VK_DOWN ))
		{
			theGameUI->Update(false);
			Global::JoystickDown = false;
		}
		//Left Trigger
		if(	Global::JoystickLeftTrigger == true  )
		{
			if ( enableShoot == true )
			{
				ippGameObject* temp = ippObjectManager::GetInstance()->GetRandomObjByTag("Enemy");
				if ( temp != NULL )
				{
					playerShip->FireMissile(temp);
					enableShoot = false;
					Global::JoystickLeftTrigger = false;
				}
			}
		}

		//Right Trigger
		if(	Global::JoystickRightTrigger == true  )
		{
			if ( enableShoot == true )
			{
				playerShip->FireBullet();
				enableShoot = false;
				Global::JoystickRightTrigger = false;
			}
		}
		// Button A
		if( Global::JoystickA == true || GetAsyncKeyState ( VK_RETURN ) )
		{
			command = theGameUI->Identity();
			Global::JoystickA = false;
		}

		if ( GetAsyncKeyState ( VK_SPACE ) )
		{
			if ( enableShoot == true ) 
			{
				playerShip->FireBullet();
				enableShoot = false;
			}
		}
		else
		{
			enableShoot = true;
		}

	}

	

	//if ( GetAsyncKeyState ( VK_RETURN ) )
	//{
	//	if ( ippObjectManager::GetInstance ()->GetRandomObjByTag ( "Enemy" ) != NULL )
	//	{
	//		playerShip->FireMissile ( ippObjectManager::GetInstance ()->GetRandomObjByTag ( "Enemy" ) );
	//	}
	//}

}
void ippGameManager::LoadLevel ()
{
	//Spawner ID 
	//Enemy Type
	//Flight Path 
	
	//If random 1, spawner 1 and 2
	// if random 2, spawner 3 and 4

	int rng = RNG ( 1, 3 );

	int temp = 0;
	if ( waveNo <= 3 )
	{
		 temp = RNG (1, 25 );
	}
	else if ( waveNo <= 5 )
	{
		 temp = RNG (25, 100 );
	}
	else if ( waveNo >= 7 )
	{
		 temp = RNG (51, 100 );
	}

	switch ( rng ) 
	{
	case 1:
		{
			LoadPreset_1 ( temp );
		}
		break;
	case 2:
		{
			LoadPreset_2 ( temp );
		}
		break;

	case 3:
		{
			LoadPreset_3 ( temp );
		}
		break;	
	}
}
void ippGameManager::LoadPreset_1 ( int difficulty )
{
	//Easy
	if ( difficulty <= 25 )
	{
		cout << "PRESET 1, DIFFI < 25" << endl;
		for ( int i = 0; i < (int)spawnerList.size(); i ++ )
		{
			//Bottom Left
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(4);
				spawnerList[i]->SetPathNo(1);
				continue;
			}

			//Bottom Right
			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(4);
				spawnerList[i]->SetPathNo(2);
				continue;
			}

			//Top Left
			if ( spawnerList[i]->GetID() == 3 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::RED );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 4 );
				spawnerList[i]->SetPathNo ( 3 );
				continue;
			}

			//Top Right
			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::RED );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo( 4 );
				spawnerList[i]->SetPathNo(4);
				continue;
			}
		}
	}
	//Medium
	else if ( difficulty <= 50)
	{
		cout << "PRESET 1, DIFFI > 25" << endl;
		for ( int i = 0; i < (int)spawnerList.size(); i ++ )
		{
			//Bottom Left
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::RED);
				spawnerList[i]->SetSpawnNo(6);
				spawnerList[i]->SetPathNo(1);
				continue;
			}
			//Bottom Right
			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::RED);
				spawnerList[i]->SetSpawnNo(6);
				spawnerList[i]->SetPathNo(2);
				continue;
			}

			if ( spawnerList[i]->GetID() == 3 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 4 );
				spawnerList[i]->SetPathNo ( 3 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 4 );
				spawnerList[i]->SetPathNo(4);
				continue;
			}
		}
	}
	//Hard
	else if ( difficulty <= 100)
	{
		cout << "PRESET 1, HARD" << endl;
		for ( int i = 0; i < (int)spawnerList.size(); i ++ )
		{
			//Bottom Left
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::RED);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(1);
				continue;
			}
			//Bottom Right
			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::RED);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(2);
				continue;
			}

			if ( spawnerList[i]->GetID() == 3 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 10 );
				spawnerList[i]->SetPathNo ( 5 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 10 );
				spawnerList[i]->SetPathNo(6);
				continue;
			}

			if ( spawnerList[i]->GetID() == 5 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::GREEN);
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 2 );
				spawnerList[i]->SetPathNo ( 3 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 6 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::GREEN );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 2 );
				spawnerList[i]->SetPathNo(4);
				continue;
			}
		}
	}

}
void ippGameManager::LoadPreset_2 ( int difficulty )
{
	//Easy
	if ( difficulty <= 25 )
	{
		cout << "PRESET 2, DIFFI < 25" << endl;
		for ( int i = 0; i < (int)spawnerList.size(); i ++ )
		{
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(4);
				spawnerList[i]->SetPathNo(1);
				continue;
			}

			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(4);
				spawnerList[i]->SetPathNo(2);
				continue;
			}

			if ( spawnerList[i]->GetID() == 3 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::RED );
				spawnerList[i]->SetDelay ( 3 );
				spawnerList[i]->SetSpawnNo ( 6 );
				spawnerList[i]->SetPathNo ( 3 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::RED );
				spawnerList[i]->SetDelay ( 3 );
				spawnerList[i]->SetSpawnNo ( 6 );
				spawnerList[i]->SetPathNo ( 2 );
				continue;
			}
		}
	}

	//Medium
	else if ( difficulty <= 50 )
	{
		cout << "PRESET 2, DIFFI > 25" << endl;

		for ( int i = 0; i < (int)spawnerList.size(); i ++ )
		{
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(1);
				continue;
			}

			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(2);
				continue;
			}

			if ( spawnerList[i]->GetID() == 3 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::GREEN);
				spawnerList[i]->SetSpawnNo(2);
				spawnerList[i]->SetPathNo(3);
				continue;
			}

			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::GREEN);
				spawnerList[i]->SetSpawnNo(2);
				spawnerList[i]->SetPathNo(4);
				continue;
			}
		}
	}

	//Hard
	else if ( difficulty <= 100)
	{
		cout << "PRESET 2, HARD" << endl;
		for ( int i = 0; i < (int)spawnerList.size(); i ++ )
		{
			//Bottom Left
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::RED);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(3);
				continue;
			}
			//Bottom Right
			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::RED);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(4);
				continue;
			}

			if ( spawnerList[i]->GetID() == 3 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 7 );
				spawnerList[i]->SetSpawnNo ( 10 );
				spawnerList[i]->SetPathNo ( 5 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 7 );
				spawnerList[i]->SetSpawnNo ( 10 );
				spawnerList[i]->SetPathNo(6);
				continue;
			}

			if ( spawnerList[i]->GetID() == 5 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::GREEN);
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 2 );
				spawnerList[i]->SetPathNo ( 3 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 6 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::GREEN );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 2 );
				spawnerList[i]->SetPathNo(4);
				continue;
			}
		}
	}
}
void ippGameManager::LoadPreset_3 ( int difficulty )
{
	//Easy
	if ( difficulty <= 25 )
	{
		cout << "PRESET 3, DIFFI < 25" << endl;
		for ( int i = 0; i < (int)spawnerList.size(); i ++ )
		{
			//Bottom Left
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(10);
				spawnerList[i]->SetPathNo(5);
				continue;
			}

			//Bottom Right
			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(10);
				spawnerList[i]->SetPathNo(6);
				continue;
			}
		}
	}
	//Medium
	else if ( difficulty <= 50)
	{
		cout << "PRESET 3, DIFFI > 25" << endl;
		for ( int i = 0; i < (int)spawnerList.size(); i ++ )
		{
			//Bottom Left
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::RED);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(5);
				continue;
			}
			//Bottom Right
			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::RED);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(6);
				continue;
			}

			if ( spawnerList[i]->GetID() == 3 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 6 );
				spawnerList[i]->SetPathNo ( 1 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 6 );
				spawnerList[i]->SetPathNo(2);
				continue;
			}
		}
	}

	//Hard
	else if ( difficulty <= 100)
	{
		cout << "PRESET 3, HARD" << endl;
		for ( int i = 0; i < (int)spawnerList.size(); i ++ )
		{
			//Bottom Left
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::RED);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(3);
				continue;
			}
			//Bottom Right
			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::RED);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(4);
				continue;
			}

			if ( spawnerList[i]->GetID() == 3 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 3 );
				spawnerList[i]->SetSpawnNo ( 10 );
				spawnerList[i]->SetPathNo ( 1 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 3 );
				spawnerList[i]->SetSpawnNo ( 10 );
				spawnerList[i]->SetPathNo ( 2 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 5 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::GREEN);
				spawnerList[i]->SetDelay ( 7 );
				spawnerList[i]->SetSpawnNo ( 2 );
				spawnerList[i]->SetPathNo ( 3 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 6 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::GREEN );
				spawnerList[i]->SetDelay ( 7 );
				spawnerList[i]->SetSpawnNo ( 2 );
				spawnerList[i]->SetPathNo(4);
				continue;
			}
		}
	}
}
void ippGameManager::TestPreset ()
{
	for ( int i = 0; i < (int)spawnerList.size(); i ++ )
	{
		if ( spawnerList[i]->GetID() == 1 )
		{
			spawnerList[i]->SetActivation ( true );
			spawnerList[i]->SetType(ippEnemy::BLUE);
			spawnerList[i]->SetSpawnNo(8);
			spawnerList[i]->SetPathNo(5);
			continue;
		}
	}
}
void ippGameManager::DeleteFlagged ()
{
	float now = glutGet ( GLUT_ELAPSED_TIME );
	for ( int i = 0; i < (int)ippObjectManager::GetInstance()->objects.size(); ++ i )
	{
		//DELETES IF FLAGGED FOR DELETION
		ippGameObject* temp = ippObjectManager::GetInstance()->GetObj(i);
		if ( temp != NULL &&
			temp->GetTag().compare ("Enemy") == 0 &&
			temp->GetDeleteFlag() == true )
		{
			//Deletes the collider attached to this object
			if ( temp->GetCollider2D() != NULL )
			{
				ippCollisionManager::GetInstance()->DeleteCollider ( temp->GetCollider2D() );
			}

			if ( temp != NULL )
			{
				ippObjectManager::GetInstance()->DeleteObj(temp);
				temp = NULL;
			}
		}
		else if ( loadFinish && 
				  now - gcPrevTime > 2 * 1000.0f &&
				  temp->GetTag().compare ("Enemy") == 0 &&
				  temp != NULL )
		{
			gcPrevTime = now;
			//DELETES IF OUTSIDE OF SCREEN
			if ( temp->GetPosition().x < 0 || temp->GetPosition().x > 800 ||
				temp->GetPosition().y < 0 || temp->GetPosition().y > 600 )
			{
				if ( temp->GetCollider2D() != NULL )
				{
					ippCollisionManager::GetInstance()->DeleteCollider ( temp->GetCollider2D() );
				}

				if ( temp != NULL )
				{
					ippObjectManager::GetInstance()->DeleteObj(temp);
					temp = NULL;
				}

			}
		}
	}
}
void ippGameManager::FireBullet ( Vec3D position, Vec3D direction )
{
	if ( bulletIndex > bufferSize - 1 )
	{
		bulletIndex = 0;
	}	

	enemyBulletList.at ( bulletIndex )->SetAlive ( true );
	enemyBulletList.at ( bulletIndex )->SetPosition ( position );
	enemyBulletList.at ( bulletIndex )->SetDirection ( direction );

	bulletIndex ++;
}
void ippGameManager::WipeEnemyFromExistence ()
{
	for ( int i = 0; i < (int)ippObjectManager::GetInstance()->objects.size(); ++ i )
	{
		//DELETES IF FLAGGED FOR DELETION
		ippGameObject* temp = ippObjectManager::GetInstance()->GetObj(i);

		if ( temp->GetTag() == "Enemy" && temp != NULL )
		{
			ippCollisionManager::GetInstance()->DeleteCollider ( temp->GetCollider2D() );

			ippObjectManager::GetInstance()->DeleteObj(temp);
			temp = NULL;
		}
	}
}
