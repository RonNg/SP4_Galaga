#pragma once
#include <GL/freeglut.h>
#include "Vec3D.h"

class ippEnemyGrid
{
private:
	int array_for_X;
	int array_for_Y;
	float size_of_ships_X;
	float size_of_ships_Y;
	float size_of_grid_X;
	float size_of_grid_Y;
	float gridposX;
	float gridposY;
	float* gridShipX;
	float* gridShipY;

public:
	ippEnemyGrid(void);
	~ippEnemyGrid(void);

	void Init( float grid_x_size, float grid_y_size, int x_arr, int y_arr, float ship_x_size, float ship_y_size );
	
	float GetGridposX();
	float GetGridposY();
	float GetGridShipX();
	float GetGridShipY();
	
	void SetGridposX( float grid_new_pos_X );
	void SetGridposY( float grid_new_pos_Y );
	void SetGridposition( Vec3D point );
	void SetGridShipX( float grid_new_ship_X );
	void SetGridShipY( float grid_new_ship_Y );

	void Render();
	void RenderShipSpots();
	void SmallSquare( float x_, float y_, float posX, float posY );

	void Update();
};

