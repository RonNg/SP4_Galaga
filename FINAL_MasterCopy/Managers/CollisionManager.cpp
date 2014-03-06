#include "CollisionManager.h"
#include <algorithm>
#include "Entities\GameObject.h"

#include "Entities\Weapons\Bullet.h"

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
	std::list<ippCollider2D*>::iterator itr = find(colliders.begin(), colliders.end(), collider );
	if ( itr != colliders.end() )
	{
		delete (*itr);
   		colliders.erase(itr);
		collider = NULL;
	}
}

void ippCollisionManager::Update()
{
	list<ippCollider2D*>::iterator itr, itr2;

	for ( itr = colliders.begin(); itr != colliders.end(); itr ++ )
	{
		for ( itr2 = itr; itr2 != colliders.end(); itr2 ++ )
		{
			if ( itr != itr2 ) // to prevent an object checking with itself
			{
				//Broad-phase
				if ( (*itr)->BroadPhaseCheck( (*itr2) ) )
				{
					//Narrow-phase
					if ( (*itr)->CollideWithObject((*itr2)) )
					{
						//Moves the itr one slot back to prevent crash
						list<ippCollider2D*>::iterator temp = itr2;
						temp--;
						if( (*itr)->GetGameObject()->OnCollisionEnter( *(itr2) ) )
						{
							itr2 = temp;
						}
					}
				}
			}
		}
	}
}

