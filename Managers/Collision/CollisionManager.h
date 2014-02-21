#pragma once
#include "Singleton.h"
#include "Colliders\Collider.h"
#include <vector>


/*
	This class will handle all your collisions
========================================================
*/

class ippCollisionManager 
	: public ippSingleton<ippCollisionManager>
{
public:

	ippCollisionManager(void);
	ippCollisionManager( ippCollisionManager const&); // Don't implement
	void operator= (ippCollisionManager const&); // Don't implement

	//Contains all of the colliders in the game world.
	std::vector<ippCollider2D*> colliders;
	void Update ();

	ippCollider2D* AddCollider ( ippGameObject* obj, Vec3D* position, float width = 0, float height = 0 );
	//Pass in the collider to delete
	void DeleteCollider ( ippCollider2D* collider ); 

	//Checks for collision
	void CheckCol();
	//Handles collision
	void HandleCol();
};

