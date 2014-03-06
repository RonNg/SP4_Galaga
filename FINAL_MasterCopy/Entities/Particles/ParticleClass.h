#pragma once
#include "Vec3D.h"
#include "Globals.h"

class ippQuadClass;

using namespace Global;

class ippParticleClass
{
private:
	ippQuadClass*		particle;
	Vec3D				pos;
	Vec3D				dir;
	bool				isActive;
	float				r, g, b;

public:
	double				lifeSpan;
	double				timeAlive;
	double				flightSpeed;

	ippParticleClass( Vec3D point, Vec3D direction, double lifeSpan );
	ippParticleClass(void);
	~ippParticleClass(void);
	
	void				Update();
	void				Render();

	void				SetActive( bool alive )
						{ this->isActive = alive; }
	
	void				SetPosition( Vec3D position )
						{ this->pos = position; }
	
	void				SetDirection( Vec3D direction )
						{ this->dir = direction; }

	bool				IsActive() 
						{ return isActive; }
};
