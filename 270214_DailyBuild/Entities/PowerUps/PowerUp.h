#pragma once
#include "entities\gameobject.h"
#include "LoadTGA\LoadTGA.h"

class ippPowerUp :
	public ippGameObject
{
public:
	ippPowerUp(void);
	ippPowerUp ( float sizeX, float sizeY );
	~ippPowerUp(void);

	//virtual void		Init ();
	void				Render ();
	void				Update ();

	void				SetAlive ( bool alive );
	void				SetType ( string powerType );

	bool				IsAlive () { return alive; }
	Vec3D				GetPos () { return position; }
	string				GetType () { return powerType; }

private:
	Vec3D position;
	string powerType;

	float sizeX;
	float sizeY;

	bool alive;

	TextureImage powerUp;
};