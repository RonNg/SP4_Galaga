#pragma once
#include "ippWeaponClass.h"
#include "ippMissile.h"



class ippMissileLauncher :
	public ippWeaponClass
{
public:
	ippMissileLauncher(void);
	~ippMissileLauncher(void);

	std::vector<ippMissile*> missileList;
	int missileIndex;

	void Init ( int numOfMissile );
	void FireMissile ( Vec3D position, Vec3D direction, Vec3D* tPosition );

	void Update ( void );
	void Render ( void );
};

