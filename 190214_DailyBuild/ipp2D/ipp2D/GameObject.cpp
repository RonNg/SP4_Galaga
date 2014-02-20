#include "GameObject.h"
#include "Collider.h"
#include "ObjectManager.h"

ippGameObject::ippGameObject(void)
	: position(0,0,0)
	, direction(0,0,0)
	, collider2D(NULL)
	, tag( "Default" )
{
}

ippGameObject::~ippGameObject(void)
{
}

void ippGameObject::SetCollider2D (float width, float height)
{
	ippCollisionManager *collisionManager = ippCollisionManager::GetInstance();
	//The game object's Collider2D will now be pointed to the Collider2D in the Collision Manager.
	//This is useful when deleting the obj from the vector list in CollisionManager
	this->collider2D = collisionManager->AddCollider( this, &position, width, height );
}

void ippGameObject::OnCollisionEnter ( ippCollider2D* col )
{
	cout << " COLLIDED " << endl;
}

void ippGameObject::Destroy(ippGameObject* obj)
{
	//Deletes the collider attached to this object
	if ( collider2D != NULL )
	{
		ippCollisionManager::GetInstance()->DeleteCollider ( this->collider2D );
		this->collider2D = NULL;
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
