#include "Camera.h"
#include <iostream>

ippCamera::ippCamera(void)
{
	SetCameraType(LAND_CAM);
	Init();
}

ippCamera::ippCamera(CAM_TYPE ct)
{
	SetCameraType(ct);
	Init();
}

ippCamera::~ippCamera(void)
{
}

void ippCamera::SetCameraType(CAM_TYPE ct) {
	CameraType = ct;
}

void ippCamera::Init(void)
{
	Position = Vec3D(0.0, 0.0, 0.0);
	Along = Vec3D(1.0, 0.0, 0.0);
	Up = Vec3D(0.0, 1.0, 0.0);
	Forward = Vec3D(0.0, 0.0, -1.0);
//	Update();
}

void ippCamera::Update() {
	gluLookAt(	Position.x, Position.y, Position.z, 
				Position.x + Forward.x, Position.y + Forward.y, Position.z + Forward.z, 
				0.0f,1.0f,0.0f);
}

Vec3D ippCamera::GetPosition() {
	return Position;
}

void ippCamera::SetPosition( GLfloat x, GLfloat y, GLfloat z )
{
	this->Position.Set( x, y, z );
}

void ippCamera::SetDirection( GLfloat x, GLfloat y, GLfloat z )
{
	this->Forward.Set( x, y, z );
}

void ippCamera::Pitch(GLfloat theta)
{
	Forward.y -= theta;
	if (Forward.y > 3.142f)
		Forward.y = 3.142f;
	else if (Forward.y < -3.142f)
		Forward.y = -3.142f;
}
void ippCamera::Yaw(GLfloat theta)
{
	Forward.x = sin(-theta);
	Forward.z = -cos(-theta);
}
void ippCamera::Roll(GLfloat theta)
{
}
void ippCamera::Walk(GLfloat delta)
{
	Position.Set( Position.x + Forward.x * delta, Position.y + Forward.y * delta, Position.z + Forward.z * delta );
}
void ippCamera::Strafe(GLfloat delta)
{
	Along = Forward.crossVec3D( Up );
	Along.Normalize();
	Position.Set( Position.x + Along.x * delta, Position.y + Along.y * delta, Position.z + Along.z * delta );
}
void ippCamera::Fly(GLfloat delta)
{
}

// Toggle HUD mode
void ippCamera::SetHUD(bool m_bHUDmode)
{
	if (m_bHUDmode)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho( 0, 800, 600, 0, -1, 1 );  // Change the 800 and 600 to soft coded
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	}
	else
	{
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
		glEnable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glEnable( GL_DEPTH_TEST );
	}
}

// Get the direction of the camera
Vec3D ippCamera::GetDirection(void)
{
	return Forward;
}
