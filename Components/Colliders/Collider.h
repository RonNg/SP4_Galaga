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
	ippGameObject*				gameObject;
	float						height, width;
	Vec3D*						objPosition;

public:
	ippCollider2D				( ippGameObject* obj, Vec3D* position, float width = 0, float height = 0 );
	~ippCollider2D				(void);

	
	ippGameObject*				GetGameObject () const { return gameObject; }
	
	/*
	====================
	Function: CollideWithObject
	====================
	*/
	virtual bool				CollideWithObject ( const ippCollider2D* col ) const;
	
	void						Debug_RenderCollider();

};

