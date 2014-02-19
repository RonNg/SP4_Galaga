#include "CollisionManager.h"
#include <algorithm>
#include "GameObject.h"

ippCollisionManager::ippCollisionManager(void)
{
}

ippCollider2D* ippCollisionManager::AddCollider ( ippGameObject* obj, Vec3D* position, float width, float height)
{
	colliders.push_back( new ippCollider2D(obj, position, width, height) );
	return colliders.back();
}
void ippCollisionManager::DeleteCollider ( ippCollider2D* collider )
{
	colliders.erase( find(

		colliders.begin(),
		colliders.end(),
		collider )
		);


}

void ippCollisionManager::Update()
{
	CheckCol();
}
void ippCollisionManager::CheckCol()
{
	//int size = colliders.size();
	for ( int i = 0; i < colliders.size(); i ++ )
	{
		for ( int j = 0; j < colliders.size(); j ++ )
		{
			if ( i != j ) //To prevent an object checking with itself
			{
				//if collider[i] has collided with any other collider 
				if ( colliders[i]->CollideWithObject ( colliders[j] ) )
				{
					colliders[i]->GetGameObject()->OnCollisionEnter(colliders[j]); //Calls the virtual function
				}
			}		
		}
	}
}
void ippCollisionManager::HandleCol()
{
}

