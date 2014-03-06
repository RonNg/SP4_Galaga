#include "GameManager.h"

#include "Globals.h"
using namespace Global;

#include "Managers\ObjectManager.h"
#include "Managers\CollisionManager.h"
#include "Systems\EnemySpawner.h"
#include "Systems\EnemyGrid.h"
#include "Entities\AI\Enemy.h"
#include "Entities\PowerUps\PowerUpManager.h"
#include "StarBackground\StarManager.h"

ippGameManager::ippGameManager(void)
	: waveNo (1)
	, loadFinish ( false )
{
	theGrid = new ippEnemyGrid();

	prevTime =  glutGet ( GLUT_ELAPSED_TIME );
	gcPrevTime = glutGet ( GLUT_ELAPSED_TIME );
}

ippGameManager::~ippGameManager(void)
{
}

void ippGameManager::Init ()
{

	greenPool = 4;
	redPool = 16;
	bluePool = 20;


	spawnerList.push_back(new ippEnemySpawner ( -100, Global::HEIGHT_RESOLUTION - 100, theGrid, 1 ) );
	spawnerList.push_back(new ippEnemySpawner ( Global::WIDTH_RESOLUTION + 100, Global::HEIGHT_RESOLUTION - 100 , theGrid, 2 ) );


	spawnerList.push_back(new ippEnemySpawner ( 100, -100, theGrid, 3 ) );
	spawnerList.push_back(new ippEnemySpawner ( Global::WIDTH_RESOLUTION - 100, -100, theGrid, 4 ) );

	spawnerList.push_back(new ippEnemySpawner ( -100, Global::HEIGHT_RESOLUTION/2, theGrid, 5 ) );
	spawnerList.push_back(new ippEnemySpawner ( Global::WIDTH_RESOLUTION + 100, Global::HEIGHT_RESOLUTION/2, theGrid, 6 ) );

	powerupManager = new ippPowerUpManager ();
	powerupManager->Init ();

	starManager = new ippStarManager ();
	starManager->Init ();
}

void ippGameManager::Update ()
{
	powerupManager->Update ();
	starManager->Update ();

	if ( !loadFinish )
	{
		LoadLevel();
		loadFinish = true;
	}

	Spawn();
	DeleteFlagged();

	totalNo = ippObjectManager::GetInstance()->GetNumberOfEnemy();

	float now = glutGet ( GLUT_ELAPSED_TIME );
	//Delays checking to every 2 seconds
	if ( ( now - prevTime ) > 3 * 1000.0f ) 
	{
		
		//Check if all enemies eliminated
		if ( totalNo <= 0 )
		{
			cout << " LEVEL COMPLETE " << endl; 
			ippObjectManager::GetInstance()->GetRandomObjByTag("Player")->GetPosition().printVect();

			waveNo ++;
			Reset();
		}

		prevTime = now;
	}
}

void ippGameManager::Render ()
{
	//theGrid->Debug_RenderGrid();
	starManager->Render ();
}

void ippGameManager::Reset ()
{
	for ( int i = 0; i < spawnerList.size(); i ++ )
	{
		spawnerList[i]->Reset();
	}

	loadFinish = false;

	theGrid->ResetGrid();

	greenPool = 4;
	redPool = 16;
	bluePool = 20;

}

void ippGameManager::Spawn()
{
	for ( int i = 0; i < spawnerList.size(); ++ i )
	{
		spawnerList[i]->Spawn();
	}
}

void ippGameManager::LoadLevel ()
{
	//Spawner ID 
	//Enemy Type
	//Flight Path 
	
	//If random 1, spawner 1 and 2
	// if random 2, spawner 3 and 4

	int rng = RNG ( 1, 2 );

	switch ( rng ) 
	{
	case 1:
		{
			int temp = RNG (1, 50 );
			cout << temp << endl;
			LoadPreset_1 ( temp );
		}
		break;
	case 2:
		{
			int temp = RNG ( 1, 50 );
			LoadPreset_2 ( temp );
		}
		break;
	}


	//TestPreset();
}

void ippGameManager::SpawnerLoad ( int index )
{
	
	int randType = RNG( 1, 3 );
	
	cout << randType << endl;

	switch ( randType )
	{
	case ippEnemy::GREEN:
		{
			
		}
		break;
	case ippEnemy::RED:
		{
			cout << "RED" << endl;
		}
		break;
	case ippEnemy::BLUE:
		{
			cout << "BLUE" << endl;
		}
		break;
	}
}

void ippGameManager::LoadPreset_1 ( int difficulty )
{
	if ( difficulty <= 25 )
	{
		cout << "PRESET 1, DIFFI < 25" << endl;
		for ( int i = 0; i < spawnerList.size(); i ++ )
		{
			//Bottom Left
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(1);
				continue;
			}

			//Bottom Right
			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(8);
				spawnerList[i]->SetPathNo(2);
				continue;
			}

			//Top Left
			if ( spawnerList[i]->GetID() == 3 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::RED );
				spawnerList[i]->SetDelay ( 2 );
				spawnerList[i]->SetSpawnNo ( 4 );
				spawnerList[i]->SetPathNo ( 3 );
				continue;
			}

			//Top Right
			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::RED );
				spawnerList[i]->SetDelay ( 2 );
				spawnerList[i]->SetSpawnNo( 4 );
				spawnerList[i]->SetPathNo(4);
				continue;
			}

			//Middle Left
			if ( spawnerList[i]->GetID() == 5 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::RED );
				spawnerList[i]->SetDelay ( 2 );
				spawnerList[i]->SetSpawnNo( 4 );
				spawnerList[i]->SetPathNo ( 1 );
				continue;
			}

			//Middle Right
			if ( spawnerList[i]->GetID() == 6 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::RED );
				spawnerList[i]->SetDelay ( 2 );
				spawnerList[i]->SetSpawnNo( 4 );
				spawnerList[i]->SetPathNo ( 2 );
				continue;
			}
		}
	}
	else if ( difficulty > 25 )
	{
		cout << "PRESET 1, DIFFI > 25" << endl;
		for ( int i = 0; i < spawnerList.size(); i ++ )
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
				spawnerList[i]->SetSpawnNo ( 8 );
				spawnerList[i]->SetPathNo ( 3 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 8 );
				spawnerList[i]->SetPathNo(4);
				continue;
			}

			//Middle Left
			if ( spawnerList[i]->GetID() == 5 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::GREEN );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo( 2 );
				spawnerList[i]->SetPathNo ( 1 );
				continue;
			}

			//Middle Right
			if ( spawnerList[i]->GetID() == 6 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::RED );
				spawnerList[i]->SetDelay ( 2 );
				spawnerList[i]->SetSpawnNo( 4 );
				spawnerList[i]->SetPathNo ( 2 );
				continue;
			}
		}
	}

}

void ippGameManager::LoadPreset_2 ( int difficulty )
{
	if ( difficulty <= 25 )
	{
		cout << "PRESET 2, DIFFI < 25" << endl;
		for ( int i = 0; i < spawnerList.size(); i ++ )
		{
			if ( spawnerList[i]->GetID() == 1 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(5);
				spawnerList[i]->SetPathNo(1);
				continue;
			}

			if ( spawnerList[i]->GetID() == 2 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType(ippEnemy::BLUE);
				spawnerList[i]->SetSpawnNo(5);
				spawnerList[i]->SetPathNo(2);
				continue;
			}

			if ( spawnerList[i]->GetID() == 3 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::RED );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 16 );
				spawnerList[i]->SetPathNo ( 3 );
				continue;
			}

			if ( spawnerList[i]->GetID() == 4 )
			{
				spawnerList[i]->SetActivation ( true );
				spawnerList[i]->SetType ( ippEnemy::BLUE );
				spawnerList[i]->SetDelay ( 5 );
				spawnerList[i]->SetSpawnNo ( 5 );
				spawnerList[i]->SetPathNo ( 2 );
				continue;
			}
		}
	}

	else if ( difficulty > 25 )
	{
		cout << "PRESET 2, DIFFI > 25" << endl;

		for ( int i = 0; i < spawnerList.size(); i ++ )
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
}

void ippGameManager::TestPreset ()
{
	for ( int i = 0; i < spawnerList.size(); i ++ )
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
	for ( int i = 0; i < ippObjectManager::GetInstance()->objects.size(); ++ i )
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
			return;
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

				return;
			}
		}
	}
}
