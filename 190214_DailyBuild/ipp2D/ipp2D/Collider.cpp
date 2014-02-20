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

bool ippCollider2D::CollideWithObject ( const ippCollider2D* col ) const
{
	return ( this->objPosition->x <= col->objPosition->x + col->width/2 &&
			col->objPosition->x <= this->objPosition->x + this->width/2 &&
			this->objPosition->y <= col->objPosition->y + col->height/2 &&
			col->objPosition->y <= this->objPosition->y + this->height/2);
}

void ippCollider2D::Debug_RenderCollider ()
{
	if ( this != NULL )
	{
		glPushMatrix();
			glTranslatef(objPosition->x, objPosition->y, 0 );
			glBegin(GL_LINE_LOOP);
				glColor3f(1.0f, 1.0f, 1.0f);
				glVertex2f(	0, 0);
				glVertex2f(	0, height);

				glVertex2f(	0, height );
				glVertex2f(	width, height );

				glVertex2f(	width, height );
				glVertex2f(	width, 0);
			glEnd();
		glPopMatrix();
	}
}


