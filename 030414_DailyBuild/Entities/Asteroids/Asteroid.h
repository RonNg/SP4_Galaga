#pragma once
#include "entities\gameobject.h"
#include "LoadTGA\LoadTGA.h"

class ippAsteroid :
	public ippGameObject
{
public:
	ippAsteroid(void);
	~ippAsteroid(void);

	void	Update ( void );
	void	Render ( void );

	void	SetSize ( float x, float y );
	void	SetAlive ( bool alive );
	void	SetSpeed ( float speed );
	void	SetRotSpeed ( float rotSpeed );
	void	SetPosition ( Vec3D position );
	void	SetDirection ( Vec3D direction );

	float	GetSizeX ( void ) { return sizeX; };
	float	GetSizeY ( void ) { return sizeY; };
	bool	IsAlive ( void ) { return alive; };

private:
	float	sizeX;
	float	sizeY;

	float	speed;
	float	rotSpeed;
	float	rotVal;

	bool	alive;

	TextureImage asteroid;
};

