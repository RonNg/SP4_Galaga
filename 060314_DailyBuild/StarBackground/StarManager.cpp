#include "StarBackground\StarManager.h"

#include "Star.h"

#include <stdlib.h>
#include <time.h>


ippStarManager::ippStarManager(void)
{
	delay = 0.0f;
	curTime = 0.0f;
	prevTime = 0.0f;
	starIndex = 0;
	maxStar = 400;
}


ippStarManager::~ippStarManager(void)
{
}

void ippStarManager::Init ( void )
{
	srand (time(NULL));

	delay = 0.0f;

	for ( int i = 0; i < maxStar; i++ )
	{
		starList.push_back ( new ippStar () );
	}

	float size = rand () % 2 + 2;
	float speed = rand () % 4 + 2;

	for ( int i = 0; i < maxStar; i++ )
	{
		Vec3D tempVec;
		tempVec.x = rand () % ( Global::WIDTH_RESOLUTION );
		tempVec.y = rand () % ( Global::HEIGHT_RESOLUTION );
		tempVec.z = 0.0f;
		starList.at ( i )->SetPosition ( tempVec );
		starList.at ( i )->SetSize ( size, size );
		starList.at ( i )->SetSpeed ( speed );
		starList.at ( i )->SetAlive ( true );
	}
}

void ippStarManager::Update ( void )
{
	
	if ( starIndex >= maxStar )
	{
		starIndex = 0;
	}



	for ( int i = 0; i < maxStar; i ++ )
	{
		starList.at ( i )->Update ();
	}
}

void ippStarManager::Render ()
{
	for ( int i = 0; i < maxStar; i ++ )
	{
		starList.at ( i )->Render ();
	}
}