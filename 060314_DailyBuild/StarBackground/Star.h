#pragma once

#include "LoadTGA\LoadTGA.h"
#include "Vec3D.h"
#include "Globals.h"

using namespace Global;

class ippStar
{
public:
	ippStar(void);
	~ippStar(void);

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

		Vec3D position;
	Vec3D direction;

private:


	float	sizeX;
	float	sizeY;

	float	speed;
	float	rotSpeed;
	float	rotVal;

	bool	alive;

	TextureImage star;
};
