#pragma once
#include "Vec3D.h"
#include "GL\freeglut.h"

#include "Globals.h"
using namespace Global;

#include <string>
using namespace std;

class ippCollider2D;


/*
========================================================

	Class : ippGameObject
	
	Description:
	ippGameObject is the base class for which all
	objects that exist in the game world MUST INHERIT.
	
	E.g. PlayerObject MUST INHERIT from GameObject
========================================================
*/
class ippGameObject
{
protected:
	Vec3D position, direction;
	string tag; // To store the object's tag. Useful for collision.
	ippCollider2D* collider2D;

public:
	ippGameObject(void);
	virtual ~ippGameObject(void);
	
	ippCollider2D* GetCollider2D () { return collider2D; }

	void SetTag ( string tag ) { this->tag = tag; }
	string GetTag () { return tag; }

	/*
	===========================

	Function : SeCollider2D

	Description:
	Use this to set the AABB size of the current collider.
	Without calling this function, the GameObject is assumed to not have a collider
	and is ignored from any collision checks.

	===========================
	*/
	virtual void SetCollider2D ( float width, float height );


	/*
	===========================

	Function : OnCollisionEnter

	Description:
	This function is a callback function that is executed
	from the CollisionManager class.

	Any derived class must override this method for their own
	collision handling.

	The argument ippCollider2D* col is passed in during the callback.
	This pointer contains basic information of the GameObject
	such as position, direction and the tag.
	===========================
	*/
	virtual bool OnCollisionEnter ( ippCollider2D* col );

	/*
	===========================

	Function : Destroy

	Description:
	This method destroys the current object. 
	
	Use this when you want to do a collision handling scenario
	where when an object collides with another it is destroyed.

	E.g.
	OnCollisionEnter ( ippCollider2D* col )
	{
		Destroy(col->gameObject);
	}

	This function will check whether the collider pointer is NULL
	first before deleting.

	===========================
	*/
	virtual void Destroy (ippGameObject* obj); 


	void Debug_RenderCollider2D();


	virtual void Init();
	virtual void Update();
	virtual void Render();

};

