#pragma once
#include "ippweaponclass.h"
class ippMissile : public ippWeaponClass
{
public:
	ippMissile ( void );
	ippMissile ( Vec3D position, Vec3D tPosition, Vec3D direction,float speed, int damage, float sizeX, float sizeY );
	~ippMissile ( void );

	void Update ( void );
	void Render ( void );

private:
	// Missile rotation variables
	bool stopRotation;
	float turnSpeed;
	float rotVal;
	Vec3D oldDirection;
	Vec3D oldTargetPosition;
};

