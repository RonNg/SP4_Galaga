#include "EnemyGrid.h"
#include <iostream>
using namespace std;

ippEnemyGrid::ippEnemyGrid(void)
:	array_for_X(0)
,	array_for_Y(0)
,	size_of_ships_X(0.0f)
,	size_of_ships_Y(0.0f)
,	size_of_grid_X(0.0f)
,	size_of_grid_Y(0.0f)
,	gridposX(0.0f)
,	gridposY(0.0f)
,	gridShipX(0)
,	gridShipY(0)
{
}

ippEnemyGrid::~ippEnemyGrid(void)
{
}

void ippEnemyGrid::Init( float grid_x_size, float grid_y_size, int x_arr, int y_arr, float ship_x_size, float ship_y_size, float grid_x_pos, float grid_y_pos )
{
	size_of_grid_X = grid_x_size;
	size_of_grid_Y = grid_y_size;

	array_for_X = x_arr;
	array_for_Y = y_arr;
	gridShipX = new float[array_for_X];
	gridShipY = new float[array_for_Y];
	
	size_of_ships_X = ship_x_size;
	size_of_ships_Y = ship_y_size;
	
	gridposX = grid_x_pos;
	gridposY = grid_y_pos;

	int slicesX = size_of_grid_X / array_for_X;
	int slicesY = size_of_grid_Y / array_for_Y;
	for( int x = 0; x < array_for_X; x++ )
	{
		for( int y = 0; y < array_for_Y; y++ )
		{
			gridShipX[x] = gridposX + x * slicesX - ( size_of_grid_X / 2 );
			gridShipY[y] = gridposY + y * slicesY - ( size_of_grid_X / 2 );
		}
	}
}

void ippEnemyGrid::Init( float grid_x_size, float grid_y_size, int x_arr, int y_arr, float ship_x_size, float ship_y_size, Vec3D grid_pos )
{
	size_of_grid_X = grid_x_size;
	size_of_grid_Y = grid_y_size;

	array_for_X = x_arr;
	array_for_Y = y_arr;
	gridShipX = new float[array_for_X];
	gridShipY = new float[array_for_Y];
	
	size_of_ships_X = ship_x_size;
	size_of_ships_Y = ship_y_size;
	
	gridposX = grid_pos.x;
	gridposY = grid_pos.y;

	int slicesX = size_of_grid_X / array_for_X;
	int slicesY = size_of_grid_Y / array_for_Y;
	for( int x = 0; x < array_for_X; x++ )
	{
		for( int y = 0; y < array_for_Y; y++ )
		{
			gridShipX[x] = gridposX + x * slicesX - ( size_of_grid_X / 2 );
			gridShipY[y] = gridposY + y * slicesY - ( size_of_grid_X / 2 );
		}
	}
}

void ippEnemyGrid::SetGridposX( float grid_new_pos_X )
{
	gridposX = grid_new_pos_X;
}

void ippEnemyGrid::SetGridposY( float grid_new_pos_Y )
{
	gridposY = grid_new_pos_Y;
}

void ippEnemyGrid::SetGridposition( Vec3D point )
{
	gridposX = point.x;
	gridposY = point.y;
}

//void ippEnemyGrid::SetGridShipX( float grid_new_ship_X )
//{
//	gridShipX = grid_new_ship_X;
//}
//
//void ippEnemyGrid::SetGridShipY( float grid_new_ship_Y )
//{
//	gridShipY = grid_new_ship_Y;
//}

void ippEnemyGrid::Render()
{
	float tempX = size_of_grid_X / 2;
	float tempY = size_of_grid_Y / 2;

	glPushMatrix();
	glTranslatef( gridposX, gridposY, 0 );
	glColor4f( 1.0f, 0.0f, 0.0f, 0.3f );
	glBegin(GL_QUADS);
	glTexCoord2f( 0, 1 ); glVertex2f( -tempX, -tempY);
	glColor4f( 0.0f, 1.0f, 0.0f, 0.3f );
	glTexCoord2f( 0, 0 ); glVertex2f( -tempX, tempY);
	glColor4f( 0.0f, 0.0f, 1.0f, 0.3f );
	glTexCoord2f( 1, 0 ); glVertex2f( tempX, tempY);
	glColor4f( 1.0f, 1.0f, 1.0f, 0.3f );
	glTexCoord2f( 1, 1 ); glVertex2f( tempX, -tempY);
	glEnd();
	glPopMatrix();

	RenderShipSpots();
}

void ippEnemyGrid::RenderShipSpots()
{
	for( int counterX = 0; counterX < array_for_X; counterX++ )
	{
		for( int counterY = 0; counterY < array_for_Y; counterY++ )
		{
			SmallSquare( size_of_ships_X, size_of_ships_Y,
						gridShipX[counterX],
						gridShipY[counterY]);
		}
	}
}

void ippEnemyGrid::SmallSquare( float x_, float y_, float posX, float posY )
{
	float tempX = x_ / 2;
	float tempY = y_ / 2;

	glPushMatrix();
	glTranslatef( posX, posY, 0 );
	glColor4f( 1.0f, 1.0f, 1.0f, 0.3f );
	glBegin(GL_QUADS);
	glTexCoord2f( 0, 1 ); glVertex2f( -tempX, -tempY);
	glTexCoord2f( 0, 0 ); glVertex2f( -tempX, tempY);
	glTexCoord2f( 1, 0 ); glVertex2f( tempX, tempY);
	glTexCoord2f( 1, 1 ); glVertex2f( tempX, -tempY);
	glEnd();
	glPopMatrix();
}