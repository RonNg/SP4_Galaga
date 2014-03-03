#include "GameObject.h"
#include "Components\Colliders\Collider.h"
#include "Managers\ObjectManager.h"

ippGameObject::ippGameObject(void)
	: position(0,0,0)
	, direction(0,1,0)
	, collider2D(NULL)
	, tag( "Default" )
{

}

ippGameObject::~ippGameObject(void)
{
	position.Set(-1337, -1337, -1337);
}

void ippGameObject::SetCollider2D (float width, float height)
{
	ippCollisionManager *collisionManager = ippCollisionManager::GetInstance();
	//The game object's Collider2D will now be pointed to the Collider2D in the Collision Manager.
	//This is useful when deleting the obj from the vector list in CollisionManager
	this->collider2D = collisionManager->AddCollider( this, &position, width, height );
}

bool ippGameObject::OnCollisionEnter ( ippCollider2D* col )
{
	return false;
}

void ippGameObject::Destroy(ippGameObject* obj)
{
	//Deletes the collider attached to this object
	if ( obj->GetCollider2D() != NULL )
	{
		ippCollisionManager::GetInstance()->DeleteCollider ( obj->GetCollider2D() );
	}

	if ( obj != NULL )
	{
		ippObjectManager::GetInstance()->DeleteObj(obj);
		obj = NULL;
	}
}

void ippGameObject::Init()
{
}

void ippGameObject::Update()
{
}

void ippGameObject::Render()
{
}

void ippGameObject::Debug_RenderCollider2D ()
{
	//if ( collider2D )
	//{
	//	this->collider2D->Debug_RenderCollider();
	//}
}
