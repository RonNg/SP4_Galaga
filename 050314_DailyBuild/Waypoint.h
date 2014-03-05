#pragma once
#include "Vec3D.h"
#include <GL/glut.h>
#include <string>

#include <iostream>
using namespace std;

class ippWaypoint
{
public:
	//Sets a waypoint directly 
	ippWaypoint( float x, float y, float range = 5.0f, string tag = "Default" );

	ippWaypoint(void);
	~ippWaypoint(void);

	Vec3D				position; //Waypoint's co-ordinates
	float				range; // Range at which unit stops moving (prevents overshooting)
	float				waypointSize; // The size of the waypoint for rendering
	bool				activate; //If waypoint is activated
	string				tag; //Useful for identifying waypoints.

	//Check if waypoint is activated
	bool				IsActivated (); 
	//Check if the unit has reached the waypoint
	bool				Reached ( Vec3D unitPos );

	void				SetWaypoint( const float x, const float y, string tag = "Default" );
	
	//Gets the direction to waypoint 	
	Vec3D				DirectionToWP ( Vec3D unitPos); //Changes unit's direction

	//Renders the waypoint
	void				Render();
};
