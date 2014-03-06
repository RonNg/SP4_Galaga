#pragma once
#include "Managers\EmitterClass.h"
#include "Vec3D.h"
#include <vector>
#include <ctime>
#include <cstdlib>

class ippEmitterManager
{
private:
	//								Variables
	static ippEmitterManager		*e_mInstance;
	bool							makeEmitter;
	int								maxEmitter;
	int								emitterIndex;
	int								particleLimit;

public:
	//								Variables
	std::vector<ippEmitter*>		ListOfEmitter;

	//								Functions
	static ippEmitterManager*		GetInstance();
	void							DropInstance();
	bool							Init( int numOfEmitters = 50, int maxNumOfParticles = 500 );
	void							Update();
	void							Render();
	//	CreateTrail(Vec3D *point) creates a EmitterClass that will create particles
	//	continuously in a given direction
	void							CreateTrail( Vec3D *point, Vec3D *direction );
	//	CreateExplosion(Vec3D *point) creates a EmitterClass that will create many
	//	particles and release all of them in all directions
	void							CreateExplosion( Vec3D &point );
	void							StopTrail( Vec3D point );

	ippEmitterManager(void);
	~ippEmitterManager(void);
};
