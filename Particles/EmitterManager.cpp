#include "EmitterManager.h"

ippEmitterManager * ippEmitterManager::e_mInstance = NULL;

ippEmitterManager::ippEmitterManager(void)
{
	makeEmitter = false;
	maxEmitter = 1000;
	emitterIndex = 0;
}

ippEmitterManager::~ippEmitterManager(void)
{
}

ippEmitterManager* ippEmitterManager::GetInstance()
{
	if( e_mInstance == NULL )
	{
		e_mInstance = new ippEmitterManager();
		srand (static_cast <unsigned> (time(0)));
	}

	return e_mInstance;
}

void ippEmitterManager::DropInstance()
{
	if( e_mInstance != NULL )
	{
		delete e_mInstance;
		e_mInstance = NULL;
	}
}

bool ippEmitterManager::Init( int numOfEmitters, int maxNumOfParticles )
{
	maxEmitter = numOfEmitters;
	particleLimit = maxNumOfParticles;
	emitterIndex = 0;
	
	Vec3D testPos = Vec3D( 400.0f, 300.0f, 0.0f );
	Vec3D *centralPos = &testPos;

	for( int i = 0; i < maxEmitter; i++ )
	{
		ListOfEmitter.push_back( new ippEmitter( centralPos, true ) );
		ListOfEmitter.at( i )->Init( particleLimit );
	}
	return true;
}

bool ippEmitterManager::Update()
{
	for( int i = 0; i < ListOfEmitter.size(); i++ )
	{
		if( ListOfEmitter.at( i )->GetActive() /*&& ListOfEmitter.at( i )->CheckAllParticles()*/ )
		{
			ListOfEmitter.at( i )->Update();
		}
	}

	return false;
}

void ippEmitterManager::Render()
{
	for( int i = 0; i < ListOfEmitter.size(); i++ )
	{
		if( ListOfEmitter.at( i )->GetActive() )
		{
			ListOfEmitter.at( i )->Render();
		}
	}
}

void ippEmitterManager::CreateTrail( Vec3D *point, Vec3D *direction )
{
	if( emitterIndex == maxEmitter )
	{
		emitterIndex = 0;
	}
	//	Give a reference address to the EmitterClass
	ListOfEmitter.at( emitterIndex )->FollowThisPosition( point );
	ListOfEmitter.at( emitterIndex )->FollowThisDirection( direction );
	ListOfEmitter.at( emitterIndex )->SetExplosive( false );
	ListOfEmitter.at( emitterIndex )->SetActive( true );
	emitterIndex++;
}

void ippEmitterManager::CreateExplosion( Vec3D *point )
{
	if( emitterIndex == maxEmitter )
	{
		emitterIndex = 0;
	}
	//	Give a reference address to the EmitterClass
	ListOfEmitter.at( emitterIndex )->FollowThisPosition( point );
	ListOfEmitter.at( emitterIndex )->SetExplosive( true );
	ListOfEmitter.at( emitterIndex )->SetActive( true );
	emitterIndex++;
}

void ippEmitterManager::StopTrail( Vec3D point )
{
	for( int i = 0; i < maxEmitter; i++ )
	{
		if( ListOfEmitter.at( i )->GetActive() )
		{
			if( ( ListOfEmitter.at( i )->GetPos() - point ).GetMagnitude() < 1.0f )
			{
				ListOfEmitter.at( i )->SetActive( false );
				break;
			}
		}
	}
}