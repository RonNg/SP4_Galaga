#include "Collider.h"
#include "GameObject.h"


ippCollider2D::ippCollider2D ( ippGameObject* obj, Vec3D* position, float width, float height )
{
	this->objPosition = position;
	this->width = width;
	this->height = height;
	this->gameObject = obj;
}

ippCollider2D::~ippCollider2D(void)
{
	if ( objPosition  != NULL )
	{
		objPosition = NULL;
	}

	if ( gameObject != NULL )
	{
		gameObject = NULL;
	}
}

//void ippCollider2D::OnCollisionEnter ( ippCollider2D* col )
//{
//}

bool ippCollider2D::CollideWithObject ( ippCollider2D* col )
{
	
	return ( this->objPosition->x <= col->objPosition->x + col->width/2 &&
			col->objPosition->x <= this->objPosition->x + this->width/2 &&
			this->objPosition->y <= col->objPosition->y + col->height/2 &&
			col->objPosition->y <= this->objPosition->y + this->height/2);
}



