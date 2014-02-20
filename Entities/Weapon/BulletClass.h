#pragma once

#include "Vec3D.h"
#include "Entities\GameObject.h"
#include "LoadTGA.h"

class ippBulletClass
	: public ippGameObject
{
public:
	ippBulletClass ( void );
	ippBulletClass ( float speed, int damage, float sizeX, float sizeY );
	~ippBulletClass ( void );

	void Update ( void );
	void Render ( void );

	void			SetRendered ( bool alive );
	void			SetPosition ( Vec3D position );
	void			SetDirection ( Vec3D direction );

	int				GetDamage ( void ) { return damage; }
	Vec3D			GetPos ( void ) { return position; }
	bool			IsAlive ( void ) { return alive; }
private:
	float			sizeX;
	float			sizeY;
	Vec3D *			tPosition;
	float			speed;
	int				damage;
	bool			alive;

	TextureImage bullet[1];
};

