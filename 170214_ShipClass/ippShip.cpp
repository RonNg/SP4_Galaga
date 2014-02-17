#include "ippShip.h"


ippShip::ippShip(float x, float y, float z)
	:position(0, 0, 0)
{
	position.Set(x, y, z );
}


ippShip::~ippShip(void)
{
}

void ippShip::Init()
{
	//Sets direction to face upwards
	direction.Set(0, 1, 0); 
	moveSpeed = 1.0f;
}
void ippShip::Update()
{

}

void ippShip::Render ()
{
	Vec3D dimensions(20.0f, 20.0f, 0);
		
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 1 ); glVertex2f( 0, 0);
			glTexCoord2f( 0, 0 ); glVertex2f( 0, dimensions.y);
			glTexCoord2f( 1, 0 ); glVertex2f( dimensions.x, dimensions.y );
			glTexCoord2f( 1, 1 ); glVertex2f( dimensions.x, 0);
		glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void ippShip::Movement ( int moveCode )
{
	switch ( moveCode )
	{
	case LEFT:
		position.x -= moveSpeed * Global::timedelta;
		break;
	case RIGHT:
		position.x += moveSpeed * Global::timedelta;
		break;

	}
}
