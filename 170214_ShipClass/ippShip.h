#pragma once
#include "Vec3D.h"
#include "GL\freeglut.h"

#include "ippGlobals.h"
using namespace Global;


class ippShip
{

public:

	ippShip(float x, float y, float z);
	~ippShip(void);

	enum movementCode_t 
	{
		LEFT,
		RIGHT
	};

	virtual void Init ();
	virtual void Render ();
	virtual void Update ();
	virtual void Movement ( int moveCode );
	
	virtual void SetSpeed ( float moveSpeed ) { this->moveSpeed = moveSpeed; }
	

private:
	Vec3D position, direction;
	float moveSpeed;

	
};

