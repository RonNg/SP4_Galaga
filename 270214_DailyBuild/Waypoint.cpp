#include "Waypoint.h"

ippWaypoint::ippWaypoint(void)
: range ( 5.0f )
, activate (false)
, position(0, 0, 0)
, waypointSize ( 10.0f )
, tag ("Default")
{
}

ippWaypoint::ippWaypoint( float x, float y, float range, string tag )
: activate (true)
, position(x, y, 0)
, waypointSize ( 10.0f )
{
	this->tag = tag;
	this->range = range;
}

ippWaypoint::~ippWaypoint(void)
{
}

void ippWaypoint::SetWaypoint ( const float x, const float y, string tag )
{
	position.x = x;
	position.y = y;
	activate = true;
}
bool ippWaypoint::IsActivated()
{
	return activate;
}
bool ippWaypoint::Reached ( Vec3D unitPos )
{
	float distance = (unitPos - position ).GetMagnitude();

	if ( distance > range )
	{
		return false;
	}

	return true;
}
Vec3D ippWaypoint::DirectionToWP ( Vec3D unitPos )
{
	//returns direction in unit should be facing to go towards waypoint
	return (position - unitPos);
}

void ippWaypoint::Render ()
{
	glPushMatrix();
		glTranslatef(position.x, position.y, 0 );
		glBegin(GL_LINE_LOOP);
			glColor3f(1.0f, 1.0f, 1.0f);
			glVertex2f(	-waypointSize, waypointSize);
			glVertex2f(	-waypointSize, -waypointSize);

			glVertex2f(	-waypointSize, -waypointSize );
			glVertex2f(	waypointSize, -waypointSize );

			glVertex2f(	waypointSize, -waypointSize );
			glVertex2f(	waypointSize, waypointSize );
		glEnd();
	glPopMatrix();
}