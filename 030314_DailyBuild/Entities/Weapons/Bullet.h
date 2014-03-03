#pragma once

#include "Vec3D.h"
#include "Entities\GameObject.h"
#include "LoadTGA\LoadTGA.h"

class ippBullet
	: public ippGameObject
{
public:
	ippBullet ( void );
	ippBullet ( float speed, float sizeX, float sizeY );
	~ippBullet ( void );

	void Update ( void );
	void Render ( void );

	void			SetAlive ( bool alive );
	void			SetPosition ( Vec3D position );
	void			SetDirection ( Vec3D direction );

	//int				GetDamage ( void ) { return damage; }
	Vec3D			GetPos ( void ) { return position; }
	bool			IsAlive ( void ) { return alive; }
private:
	float			sizeX;
	float			sizeY;
	//Vec3D *			tPosition;
	float			speed;
	//int				damage;
	bool			alive;

	TextureImage bullet[1];

	bool OnCollisionEnter ( ippCollider2D* col );
};

