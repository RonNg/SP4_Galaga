#include "ippEnemyGrid.h"


ippEnemyGrid::ippEnemyGrid(void)
:	gridposX(0.0f)
,	gridposY(0.0f)
,	gridShipX(0)
,	gridShipY(0)
{
}

ippEnemyGrid::~ippEnemyGrid(void)
{
}

void ippEnemyGrid::Init( float x_size, float y_size, int x_num, int y_num )
{
	size_of_grid_X = x_size;
	size_of_grid_Y = y_size;
	array_for_X = x_num;
	array_for_Y = y_num;
	gridShipX = new float[array_for_X];
	gridShipX = new float[array_for_Y];
}

float ippEnemyGrid::GetGridposX()
{
	return gridposX;
}

float ippEnemyGrid::GetGridposY()
{
	return gridposY;
}

//float ippEnemyGrid::GetGridShipX()
//{
//	return gridShipX;
//}
//
//float ippEnemyGrid::GetGridShipY()
//{
//	return gridShipY;
//}

void ippEnemyGrid::SetGridposX( float grid_new_pos_X )
{
	gridposX = grid_new_pos_X;
}

void ippEnemyGrid::SetGridposY( float grid_new_pos_Y )
{
	gridposY = grid_new_pos_Y;
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
	glPushMatrix();
	glTranslatef( gridposX, gridposY, 0 );
	glColor4f( 1.0f, 1.0f, 1.0f, 0.3f );
	glBegin(GL_QUADS);
	glTexCoord2f( 0, 1 ); glVertex2f( 0, 0);
	glTexCoord2f( 0, 0 ); glVertex2f( 0, size_of_grid_Y);
	glTexCoord2f( 1, 0 ); glVertex2f( size_of_grid_X, size_of_grid_Y);
	glTexCoord2f( 1, 1 ); glVertex2f( size_of_grid_X, 0);
	glEnd();
	glPopMatrix();

	RenderShipSpots();
}

void ippEnemyGrid::RenderShipSpots()
{
	int slicesX = size_of_grid_X / array_for_X;
	int slicesY = size_of_grid_Y / array_for_Y;

	for( int counterX = 0; counterX < array_for_X; counterX++ )
	{
		for( int counterY = 0; counterY < array_for_Y; counterY++ )
		{
			SmallSquare( 10.0f, 10.0f, gridposX + counterX * slicesX, gridposY + counterY * slicesY );
		}
	}
}

void ippEnemyGrid::SmallSquare( float x_, float y_, float posX, float posY )
{
	glPushMatrix();
	glTranslatef( posX, posY, 0 );
	glColor4f( 1.0f, 1.0f, 1.0f, 0.3f );
	glBegin(GL_QUADS);
	glTexCoord2f( 0, 1 ); glVertex2f( 0, 0);
	glTexCoord2f( 0, 0 ); glVertex2f( 0, y_);
	glTexCoord2f( 1, 0 ); glVertex2f( x_, y_);
	glTexCoord2f( 1, 1 ); glVertex2f( x_, 0);
	glEnd();
	glPopMatrix();
}