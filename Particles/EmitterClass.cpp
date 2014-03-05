#include "EmitterClass.h"
#include "ParticleClass.h"

ippEmitter::ippEmitter( Vec3D *point, bool explosion )
{
	//	Then give pointer an address to point to
	pos = point;

	dir = Vec3D(0,0,0);
	isExplosion = explosion;
	hasExploded = false;
	active = true;
	timeLastCreated = 0.0f;
	particleIndex = maxParticles = 0;
}

ippEmitter::ippEmitter(void)
{
	pos = new Vec3D(0,0,0);
	dir = Vec3D(0,0,0);
	isExplosion = false;
	hasExploded = false;
	active = true;
	timeLastCreated = 0.0f;
	particleIndex = maxParticles = 0;
}

ippEmitter::~ippEmitter(void)
{
	if(pos) delete pos;
	pos = NULL;
}

void ippEmitter::SetExplosive( bool explosion )
{
	isExplosion = explosion;
	hasExploded = false;
}

bool ippEmitter::CheckAllParticles()
{
	int counter = 0;
	for( int i = 0; i < ListOfQuad.size(); i++ )
	{
		if( ListOfQuad.at( i )->IsActive() == true )
		{
			counter++;
		}
	}
	if( counter != 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ippEmitter::TimeHasPass( double timeToPass )
{
	timeLastCreated += Global::timedelta;
	if( timeLastCreated > timeToPass )
	{
		timeLastCreated = 0.0f;
		return true;
	}
	else
	{
		return false;
	}
}

void ippEmitter::Create()
{
	if( isExplosion )
	{
		if( hasExploded == false )
		{
			ParticleExplosion();
		}
	}
	else
	{
		if( TimeHasPass( 0.1f ) )
		{
			ParticleTrail();
		}
	}
}

void ippEmitter::ParticleTrail()
{
	if( particleIndex == maxParticles )
	{
		particleIndex = 0;
	}
	ListOfQuad.at( particleIndex )->SetActive( true );
	ListOfQuad.at( particleIndex )->SetDirection( SpreadDirection( dir ) );
	ListOfQuad.at( particleIndex )->SetPosition( *pos );
	particleIndex++;
}

void ippEmitter::ParticleExplosion()
{
	for( int i = 0; i < maxParticles; i++ )
	{
		ListOfQuad.at( i )->SetActive( true );
		ListOfQuad.at( i )->SetDirection( RandomDirection() );
		ListOfQuad.at( i )->SetPosition( *pos );
	}
	hasExploded = true;
}

Vec3D ippEmitter::RandomDirection()
{
	float randomAngle = static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( 6.283185308f ) ) );
	float randomVelocity = static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( 10.0f ) ) );
	Vec3D result = Vec3D( cos( randomAngle ) * randomVelocity, sin( randomAngle ) * randomVelocity, 0.0f );

	return result;
}

Vec3D ippEmitter::SpreadDirection( Vec3D dir )
{
	Vec3D reverseDir = dir * -1;
	float v_xDiff = ( static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( 10 ) ) ) - 5 ) + reverseDir.x;
	
	float v_yDiff = ( static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( 10 ) ) ) - 5 ) + reverseDir.y;

	Vec3D result = Vec3D( v_xDiff, v_yDiff, 0.0f );
	return result;
}

bool ippEmitter::Init( int counter, int maxLifeSpanOfParticle, int minLifeSpanOfParticle )
{
	maxParticles = counter;
	Vec3D nullDir = Vec3D(0,0,0);
	Vec3D nullPos = Vec3D(0,0,0);
	
	float randomLifeSpanOfParticle;

	for( int i = 0; i < counter; i++ )
	{
		randomLifeSpanOfParticle = rand() % maxLifeSpanOfParticle + minLifeSpanOfParticle;

		ListOfQuad.push_back( new ippParticleClass( nullPos, nullDir, randomLifeSpanOfParticle ) );
		printf( "%3.3f\n", randomLifeSpanOfParticle );
	}
	return true;
}

bool ippEmitter::Update()
{
	Create();

	for( int i = 0; i < ListOfQuad.size(); i++ )
	{
		if( ListOfQuad.at( i )->IsActive() )
		{
			ListOfQuad.at( i )->Update();
		}
	}

	if( CheckAllParticles() )
	{
		return false;
	}
	else
	{
		return true;
	}
}

void ippEmitter::Render()
{
	for( int i = 0; i < ListOfQuad.size(); i++ )
	{
		if( ListOfQuad.at( i )->IsActive() )
		{
			ListOfQuad.at( i )->Render();
		}
	}
}