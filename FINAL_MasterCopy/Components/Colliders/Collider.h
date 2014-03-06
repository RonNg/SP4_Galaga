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

//class ippSphereCollider2D 
//{ 
//protected:
//	ippGameObject*				gameObject;
//	Vec3D*						objPosition;
//	float						radius;
//	
//public:
//	ippSphereCollider2D			( ippGameObject* obj, Vec3D* position, float radius = 0.0f );
//	~ippSphereCollider2D		( void );
//
//	ippGameObject*				GetGameObject() const { return gameObject; } 
//	bool						CollideWithObject ( const ippCollider2D* col ) const;
//
//};


class ippCollider2D
{
protected:
	ippGameObject*				gameObject;
	float						height, width, radius;
	Vec3D*						objPosition;
	

public:
	ippCollider2D				( ippGameObject* obj, Vec3D* position, float width = 0, float height = 0 );
	~ippCollider2D				( void );
	
	ippGameObject*				GetGameObject () const { return gameObject; }
	
	/*
	====================
	Function: CollideWithObject
	====================
	*/
	bool						CollideWithObject ( const ippCollider2D* col ) const;
	bool						BroadPhaseCheck ( const ippCollider2D* col ) const ;

	void						Debug_RenderCollider();

};

