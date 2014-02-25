#include "GameManager.h"

#include "Globals.h"
using namespace Global;

#include "Managers\ObjectManager.h"

ippGameManager::ippGameManager(void)
	: waveNo (1)
	, levelNo (0)
	, loadFinish ( false )
{
}

ippGameManager::~ippGameManager(void)
{
}

void ippGameManager::Init ()
{
	spawnerList.push_back(new ippEnemySpawner ( -100, Global::HEIGHT_RESOLUTION, 1 ) );
	spawnerList.push_back(new ippEnemySpawner ( Global::WIDTH_RESOLUTION + 100, Global::HEIGHT_RESOLUTION, 2 ) );
}

void ippGameManager::Update ()
{
	LoadLevel();

	for ( int i = 0; i < spawnerList.size(); ++ i )
	{
		if ( spawnerList[i]->IsActivated() )
		{
			spawnerList[i]->Spawn(spawnerList[i]->GetID());
		}
	}
}

void ippGameManager::StartNextWave ()
{
	waveNo ++;
}

void ippGameManager::StartNextLevel ()
{
	levelNo ++;
	waveNo = 1;
}

void ippGameManager::LoadLevel ()
{
	if ( !loadFinish )
	{
		int activateID = 1; //Spawners to activate

		for ( int i = 0; i < spawnerList.size(); i ++ )
		{
			if ( spawnerList[i]->GetID() == activateID )
			{
				spawnerList[i]->SetActivation ( true );
			}
		}
		loadFinish = true;
	}
}




