#pragma once
#include "Vec3D.h"
#include "GL\freeglut.h"

#include "Globals.h"
using namespace Global;

class ippCollider2D;

class ippGameObject
{
protected:
	Vec3D position, direction;
	string tag; // To store the object's tag. Useful for collision.
	ippCollider2D* collider2D;

public:
	ippGameObject(void);
	~ippGameObject(void);
	
	virtual void SetCollider2D ( float width, float height );
	virtual void OnCollisionEnter ( ippCollider2D* col );
	virtual void Destroy (); // Call this when you want to destroy the game object

};

