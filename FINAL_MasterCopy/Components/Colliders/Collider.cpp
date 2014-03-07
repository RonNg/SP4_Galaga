#include "Collider.h"
#include "Entities\GameObject.h"


ippCollider2D::ippCollider2D ( ippGameObject* obj, Vec3D* position, float width, float height )
{
	this->objPosition = position;
	this->width = width;
	this->height = height;
	this->gameObject = obj;
	radius = 50.0f;
	
}
ippCollider2D::~ippCollider2D(void)
{
}

bool ippCollider2D::BroadPhaseCheck ( const ippCollider2D* col ) const 
{
	double dx = col->gameObject->GetPosition().x - this->objPosition->x;
	double dy = col->gameObject->GetPosition().y - this->objPosition->y;
	dx *= dx;
	dy *= dy;
	double distanceSquared = dx + dy;
	double radiusSquared = radius * radius;
	return distanceSquared <= radiusSquared;
}

bool ippCollider2D::CollideWithObject ( const ippCollider2D* col ) const
{
	if ( this->objPosition->x + this->width/2 < col->objPosition->x - col->width/2 ||
		 this->objPosition->y + this->width/2 < col->objPosition->y - col->height/2 ||
		 this->objPosition->x - this->width/2 > col->objPosition->x + col->width/2 ||
		 this->objPosition->y - this->width/2 > col->objPosition->y + col->height/2 )
	{
		return false;
	}

	return true;

}

void ippCollider2D::Debug_RenderCollider ()
{
	if ( this != NULL )
	{
		glPushMatrix();
			glTranslatef(objPosition->x - width/2, objPosition->y - height/2, 0 );
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

	/*	glPushMatrix();		
		glTranslatef(objPosition->x, objPosition->y, 0 );

			glBegin(GL_LINE_LOOP);
			for(int i=0; i<=360; i++)
			{
				const float angle = i * DEGTORAD;
				glVertex2f(radius * cos(angle), radius * sin(angle));
			}
			glEnd();
		glPopMatrix();*/
	}
}


