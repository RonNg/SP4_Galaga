#include "Bullet.h"

Bullet::Bullet(void)
{
	//Sets parent class position and direction
	coPosition = &bulletPosition;	
	coDirection = &bulletDirection;

	//DO NOT EDIT
	radius = 2.0f;

	min.Set(-radius, -radius, 0.0f);
	max.Set(radius, radius, 0.0f); 
	
	coMin = &min;
	coMax = &max;
	
	//Default speed
	bulletSpeed = 10.0f;

	coSpeed = &bulletSpeed;

	//Default range
	bulletRange = 500;



	Alive = false;
	

	

}

Bullet::~Bullet(void)
{
}

void Bullet::SetSpeed (const float speed)
{
	bulletSpeed = speed;
}

void Bullet::ConstrainBullet(const int leftBorder, const int rightBorder, const int topBorder, const int bottomBorder, idMap *game_Map, const float timeDiff)
{
	if (bulletPosition.x < leftBorder)
	{
		bulletPosition.x = leftBorder;
		Alive = false;

		if (game_Map->mapOffset_x < 0)
			game_Map->mapOffset_x = 0; 
	}

	else if (bulletPosition.x > rightBorder)
	{
		bulletPosition.x = rightBorder;
		Alive = false;

		if (game_Map->mapOffset_x > game_Map->theMap_Width)	//Change to soft coded
			game_Map->mapOffset_x = game_Map->theMap_Width;
	}

	if (bulletPosition.y < topBorder)
	{
		bulletPosition.y = topBorder;
		Alive = false;
	}

	else if (bulletPosition.y > bottomBorder)
	{
		bulletPosition.y = bottomBorder;
		Alive = false;
	}
}

//Creates bullet with a vector
void Bullet::Create(const Vec3D mousePos, const Vec3D characterPos)
{
	//Bullet direction
	bulletDirection.x = mousePos.x - characterPos.x ;
	bulletDirection.y = mousePos.y - characterPos.y - 10;
	bulletDirection.z = 0.0f; 

	bulletDirection.Normalize();
	
	//Bullet origin
	bulletPosition.x = characterPos.x;
	bulletPosition.y = characterPos.y + 10;
	bulletPosition.z = 0.0f;

	Alive = true;
}

void Bullet::Update(float mapOffset_x)
{
	if(bulletDirection.x >= bulletPosition.x + bulletRange || 
		bulletDirection.y >= bulletPosition.y + bulletRange || 
		bulletDirection.z >= bulletPosition.z + bulletRange)
	{
		Alive = false;
	}

	if(Alive)
	{
		
		bulletPosition += bulletDirection * bulletSpeed;

		int size = 5.0f;

		glPushMatrix();
			glColor3f(1.0f, 1.0f, 1.0f);


			glTranslatef(bulletPosition.x, bulletPosition.y, 0);
			glBegin(GL_QUADS);
				glVertex2f(-radius, radius);
				glVertex2f(-radius, -radius);
				glVertex2f(radius, -radius);
				glVertex2f(radius, radius);
			glEnd();


		glPopMatrix();
	}
}


