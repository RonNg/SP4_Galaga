#pragma once
#include <iostream>
#include "GL/freeglut.h"
#include "Vec3D.h"

class ippGameObject;

/*
========================================================

	ippCollider2D is a 2D AABB collision
	class. All collidable objects should inherit 
	this.
========================================================
*/
class ippCollider2D
{
protected:


public:
	ippCollider2D ( ippGameObject* obj, Vec3D* position, float width = 0, float height = 0 );
	~ippCollider2D(void);
	ippGameObject* gameObject;
	float height, width;
	Vec3D* objPosition;
	
	/*
	====================
	OnCollisionEnter

	Description:
	Callback function. This function is executed when the collision manager detects a collision between two objects.
	Each object will call it's own OnCollisionEnter method.
	====================
	*/
	//virtual void OnCollisionEnter( ippCollider2D* col );
	virtual bool CollideWithObject ( ippCollider2D* col );

};

