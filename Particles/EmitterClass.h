#pragma once
#include "Globals.h"
#include "Vec3D.h"
#include <vector>

class ippParticleClass;

using namespace Global;

class ippEmitter
{
private:
	//								Variables
	Vec3D*							pos;
	Vec3D							dir;
	std::vector<ippParticleClass*>	ListOfQuad;

	bool							active;
	bool							isExplosion;
	bool							hasExploded;

	int								particleIndex;
	int								maxParticles;
	
	double							timeLastCreated;

	//								Functions
	bool		TimeHasPass			( double timeToPass );
	void		Create				();
	//			Create() calls ParticleTrail() OR ParticleExplosion()
	void		ParticleTrail		();
	//			ParticleTrail() creates particles over time
	void		ParticleExplosion	();
	//			ParticleExplosion() creates particles in all direction
	Vec3D		RandomDirection		();
	//			RandomDirection() gives a random direction from 
	Vec3D		SpreadDirection		( Vec3D dir );
	//			SpreadDirection(Vec3D dir) returns a random direction 
	//			with the given direction from Vec3D dir

public:
	//								Functions
	bool		Init				( int counter, int  maxLifeSpanOfParticle = 59 , int minLifeSpanOfParticle = 20 );
	//	Init(int counter, float maxLifeSpanOfParticle)
	//	is called in EmitterManager.h 
	//	which will create particles with life span ranging from
	//	maxLifeSpanOfParticle and minLifeSpanOfParticle
	bool		Update				();
	void		Render				();

	void		SetExplosive		( bool explosion );
	bool		CheckAllParticles	();
	//	CheckAllParticles() returns true when there are no more particles alive

	Vec3D		GetPos				()
				{	return *pos;	}

	void		FollowThisPosition	( Vec3D *point )
				{	pos = point;	}
	void		FollowThisDirection	( Vec3D *direction )
				{	dir = *direction;	}

	void		SetActive			( bool active )
				{	this->active = active;	}
	bool		GetActive			()
				{	return active;	}

	ippEmitter( Vec3D *point, bool explosion );
	ippEmitter(void);
	~ippEmitter(void);

};

