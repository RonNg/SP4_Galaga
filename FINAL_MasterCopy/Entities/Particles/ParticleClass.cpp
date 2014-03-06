#include "ParticleClass.h"
#include "Entities\QuadClass.h"

ippParticleClass::ippParticleClass( Vec3D point, Vec3D direction, double lifeSpan )
{
	this->pos = point;
	this->dir = direction;
	this->lifeSpan = lifeSpan;
	timeAlive = 0.0f;
	isActive = false;

	particle = new ippQuadClass();
	particle->SetLW( 5.0f, 5.0f );
	r = static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( 1.0 ) ) ) + 0.0f;
	g = static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( 1.0 ) ) ) + 0.0f;
	b = static_cast<float>( rand() ) / ( static_cast<float>( RAND_MAX / ( 1.0 ) ) ) + 0.0f;
	particle->SetRGBA( r, g, b, 1.0f );
}

ippParticleClass::ippParticleClass(void)
{
	pos = dir = Vec3D(0,0,0);
	timeAlive = flightSpeed = 0.0f;
	isActive = true;
}

ippParticleClass::~ippParticleClass(void)
{
}

void ippParticleClass::Update()
{
	timeAlive += Global::timedelta;
	particle->ReduceAlpha(5.0f/lifeSpan);
	if( timeAlive > lifeSpan )
	{
		timeAlive = 0.0f;
		particle->MaxAlpha();
		isActive = false;
	}
	if( pos.x < 0.0f || pos.x > 800.0f )
	{
		if( pos.y < 0.0f || pos.y > 600.0f )
		{
			timeAlive = 0.0f;
			isActive = false;
		}
	}
	pos += dir * Global::timedelta;
	particle->SetXY( pos.x, pos.y );
}

void ippParticleClass::Render()
{
	particle->DrawQuads();
}