#pragma once
#include "GameObject.h"

class ippQuadClass;
class ippWeaponClass;
class ippGameObject;
class Vec3D;
class vector;

using namespace Global;


class ippShip 
	: public ippGameObject
{

public:
	ippShip(float x, float y, float z);
	~ippShip(void);

	std::vector<ippWeaponClass*> weaponList;
	
	enum movementCode_t 
	{
		LEFT,
		RIGHT
	};

	void	Init ();
	void	Render ();
	void	Update ();
	void	Movement ( int moveCode );
	void	FireBullet ();
	
	void	SetSpeed ( float moveSpeed ) { this->moveSpeed = moveSpeed; }
	Vec3D	GetPos ( void ) { return position; }

	void OnCollisionEnter ( ippCollider2D* col );

private:
	ippQuadClass*	ship;
	float			moveSpeed;

	
};

