#pragma once

#include "Vec3D.h"

#include "GL\freeglut.h"


#include <vector>
/*
=======================

This is the message board for Enemies
Enemies will call functions from this class
and get an allocated grid.

=======================
*/

class ippWaypoint;

class ippEnemyGrid
{
public:
	enum section_t
	{
		FIRST_SECTION = 1,
		SECOND_SECTION,
		THIRD_SECTION
	};
private:
	
	//Each section element contains a position and a boolean.  
	//The boolean is to keep track of occupancy. False = occupied and vice versa

	
	std::vector< std::pair<ippWaypoint, bool> >		firstSection; 
	int					fsRow;						// First section rows
	int					fsCol;						// First section number of cols
	

	std::vector< std::pair<ippWaypoint, bool> >		secondSection; 
	int					ssRow;
	int					ssCol;

	std::vector< std::pair<ippWaypoint, bool> >		thirdSection; 
	int					tsRow;
	int					tsCol;

	//std::vector< std::pair < ippWaypoint, bool > >		theGrid;
	//int						row;
	//int						col;
	//

public:
	ippEnemyGrid(void);
	~ippEnemyGrid(void);

	
	//Request slot returns the iterator for easier access
	ippWaypoint* RequestSlot ( int section );
	void DeallocateSlot ( ippWaypoint* waypoint );

	void Init ();
	void Debug_RenderGrid ();

	void ResetGrid ();


};

