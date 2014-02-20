#pragma once
#include "Vec3D.h"
#include <GL/glut.h>

class ippWaypoint
{
public:
	ippWaypoint(void);
	~ippWaypoint(void);

	Vec3D				position; //Waypoint's co-ordinates
	float				range; // Range at which unit stops moving (prevents overshooting)
	float				waypointSize; // The size of the waypoint for rendering
	bool				activate; //If waypoint is activated

	//Check if waypoint is activated
	bool				isActivated (); 
	//Check if the unit has reached the waypoint
	bool				Reached ( Vec3D unitPos );

	void				SetWaypoint( const float x, const float y );
	
	//Gets the direction to waypoint 	
	Vec3D				DirectionToWP ( Vec3D unitPos); //Changes unit's direction

	//Renders the waypoint
	void				Render();
};
