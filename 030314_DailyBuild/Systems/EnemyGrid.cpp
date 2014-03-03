#include "EnemyGrid.h"

#include "Globals.h"

#include "Waypoint.h"
using namespace Global;

ippEnemyGrid::ippEnemyGrid(void)
	: fsRow ( 1 )	
	, fsCol ( 4 )
	, ssRow ( 2 )
	, ssCol ( 8 )
	, tsRow ( 2 )
	, tsCol ( 10 )
{
	//First Section init
	float startPos = -50.0f;
	for ( int i = 0; i < fsRow; ++ i )
	{
		for ( int j = 0; j < fsCol; ++ j )
		{
			firstSection.push_back ( std::make_pair ( ippWaypoint ( Global::WIDTH_RESOLUTION/2 + ( startPos + j * 50.0f ), Global::HEIGHT_RESOLUTION/2 - 250.0f, 5.0f, "Grid Waypoint" ), false ) );
		}
	}
	
	startPos = -150.0f;
	for ( int i = 0; i < ssRow; ++ i )
	{
		for ( int j = 0; j < ssCol; ++ j )
		{
			secondSection.push_back ( std::make_pair ( ippWaypoint ( Global::WIDTH_RESOLUTION/2 + ( startPos + j * 50.0f ), Global::HEIGHT_RESOLUTION/2 - ( 200.0f + i * 25.0f ), 5.0f, "Grid Waypoint" ), false ) );
		}
	}

	startPos = -200.0f;
	for ( int i = 0; i < tsRow; ++ i )
	{
		for ( int j = 0; j < tsCol; ++ j )
		{
			thirdSection.push_back ( std::make_pair ( ippWaypoint ( Global::WIDTH_RESOLUTION/2 + ( startPos + j * 50.0f ), Global::HEIGHT_RESOLUTION/2 - ( 150.0f + i * 25.0f ), 5.0f, "Grid Waypoint" ), false ) );
		}
	}

}


ippEnemyGrid::~ippEnemyGrid(void)
{
}

void ippEnemyGrid::Init ()
{
}

void ippEnemyGrid::Debug_RenderGrid ( )
{
	std::vector< std::pair<ippWaypoint, bool> >::iterator itr;
	for ( itr = firstSection.begin(); itr != firstSection.end(); ++ itr )
	{	
		(*itr).first.Render();
	}

	for ( itr = secondSection.begin(); itr != secondSection.end(); ++ itr )
	{	
		(*itr).first.Render();
	}

	for ( itr = thirdSection.begin(); itr != thirdSection.end(); ++ itr )
	{	
		(*itr).first.Render();
	}
}

ippWaypoint* ippEnemyGrid::RequestSlot ( int section )
{
	if ( section == FIRST_SECTION )
	{
		while ( true )
		{
			//Randomly allocates a slot
			int randomNo = rand () %  ( firstSection.size() );

			//Checks if slot is occupied.
			if ( firstSection[randomNo].second == false )
			{
				//Sets slot to occupied
				firstSection[randomNo].second = true;
				return &( firstSection[randomNo].first );
			}
		}
	}
	else if ( section == SECOND_SECTION )
	{
		while ( true )
		{
			int randomNo = rand () %  ( secondSection.size()  );

			if ( secondSection[randomNo].second == false )
			{
				secondSection[randomNo].second = true;
				return &( secondSection[randomNo].first );
			}
		}
	}
	else if ( section == THIRD_SECTION )
	{
		while ( true )
		{
			int randomNo = rand () %  ( thirdSection.size() );

			if ( thirdSection[randomNo].second == false )
			{
				thirdSection[randomNo].second = true;
				return &( thirdSection[randomNo].first );
			}
		}
	}
	
}

void ippEnemyGrid::DeallocateSlot ( ippWaypoint* waypoint )
{
	////Finds in first section
	//std::list<ippWaypoint*>::iterator itr = find ( firstSection.begin(), firstSection.end(), waypoint );
	//
	////If waypoint not found in first section
	//if ( itr == firstSection.end() )
	//{
	//	//Finds in second section
	//	itr = find ( secondSection.begin(), secondSection.end(), waypoint );
	//}
	////If waypoint not found in second section
	//else if ( itr == secondSection.end() )
	//{
	//	//Finds in third section
	//	itr = find ( thirdSection.begin(), thirdSection.end(), waypoint );
	//}

	
}
void ippEnemyGrid::ResetGrid () 
{
	for ( int i = 0; i < firstSection.size(); ++ i )
	{
		//Sets slot to unoccupied
		firstSection[i].second = false;
	}

	for ( int i = 0; i < secondSection.size(); ++ i )
	{
		//Sets slot to unoccupied
		secondSection[i].second = false;
	}

	for ( int i = 0; i < thirdSection.size(); ++ i )
	{
		//Sets slot to unoccupied
		thirdSection[i].second = false;
	}
}