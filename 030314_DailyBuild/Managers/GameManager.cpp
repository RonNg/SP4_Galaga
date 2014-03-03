#include "GameManager.h"

#include "Globals.h"
using namespace Global;

#include "Managers\ObjectManager.h"
#include "Systems\EnemySpawner.h"
#include "Systems\EnemyGrid.h"
#include "Entities\AI\Enemy.h"

ippGameManager::ippGameManager(void)
	: waveNo (1)
	, loadFinish ( false )
{
	theGrid = new ippEnemyGrid();
	prevTime =  glutGet ( GLUT_ELAPSED_TIME );
}

ippGameManager::~ippGameManager(void)
{
}

void ippGameManager::Init ()
{
	spawnerList.push_back(new ippEnemySpawner ( -100, Global::HEIGHT_RESOLUTION, theGrid, 1 ) );
	spawnerList.push_back(new ippEnemySpawner ( Global::WIDTH_RESOLUTION + 100, Global::HEIGHT_RESOLUTION, theGrid, 2 ) );
}

void ippGameManager::Update ()
{
	if ( !loadFinish )
	{
		LoadLevel();
		loadFinish = true;
	}

	Spawn();

	greenNo = ippObjectManager::GetInstance()->GetNumberOfEnemyType(ippEnemy::GREEN);
	redNo = ippObjectManager::GetInstance()->GetNumberOfEnemyType(ippEnemy::RED);
	greenNo = ippObjectManager::GetInstance()->GetNumberOfEnemyType(ippEnemy::BLUE);
	totalNo = ippObjectManager::GetInstance()->GetNumberOfEnemy();


	float now = glutGet ( GLUT_ELAPSED_TIME );
	//Delays checking to every 2 seconds
	if ( ( now - prevTime ) * 1000.0f > 2 ) 
	{
		//Check if all enemies eliminated
		if ( totalNo <= 0 )
		{
			cout << " LEVEL COMPLETE " << endl;
			waveNo ++;
			Reset();
		}
	}
}

void ippGameManager::Render ()
{
	theGrid->Debug_RenderGrid();

}

void ippGameManager::Reset ()
{
	for ( int i = 0; i < spawnerList.size(); i ++ )
	{
		spawnerList[i]->Reset();
	}

	loadFinish = false;

	theGrid->ResetGrid();
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
	switch ( waveNo )
	{
	case 1 :
		LoadLevel_1();
		break;
	case 2:
		LoadLevel_2();
		break;
	}
}

void ippGameManager::LoadLevel_1 ()
{
	//Each spawner has different properties
	for ( int i = 0; i < spawnerList.size(); i ++ )
	{
		if ( spawnerList[i]->GetID() == 1 )
		{
			spawnerList[i]->SetActivation ( true );
			spawnerList[i]->SetSpawnNo(8);
			spawnerList[i]->SetPathNo(1);
			continue;
		}

		if ( spawnerList[i]->GetID() == 2 )
		{
			spawnerList[i]->SetActivation ( true );
			spawnerList[i]->SetSpawnNo(8);
			spawnerList[i]->SetPathNo(2);
			continue;
		}
	}
}

void ippGameManager::LoadLevel_2 ()
{
	//Each spawner has different properties
	for ( int i = 0; i < spawnerList.size(); i ++ )
	{
		if ( spawnerList[i]->GetID() == 1 )
		{
			spawnerList[i]->SetActivation ( true );
			spawnerList[i]->SetSpawnNo(8);
			spawnerList[i]->SetPathNo(1);
			continue;
		}

		if ( spawnerList[i]->GetID() == 2 )
		{
			spawnerList[i]->SetActivation ( true );
			spawnerList[i]->SetSpawnNo(8);
			spawnerList[i]->SetPathNo(2);
			continue;
		}
	}
}


