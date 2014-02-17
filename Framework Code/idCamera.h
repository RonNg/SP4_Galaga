#pragma once

#include "Vec3D.h"
#include <GL/freeglut.h>

class idCamera
{
public:
	enum CAM_TYPE { LAND_CAM, AIR_CAM };

private:
	CAM_TYPE CameraType;
	Vec3D Position;
	Vec3D Along;
	Vec3D Up;
	Vec3D Forward;

public:

	//Default constructor
	idCamera(void);
	//User Specified Constructor
	idCamera(CAM_TYPE ct);
	//Default Destructor
	~idCamera(void);

	//Set camera tpye : CAM_TYPE LAND_CAM, CAM_TYPE AIR_CAM
	void SetCameraType(CAM_TYPE ct);
	//
	void Init(void);
	void Update();
	Vec3D GetPosition();
	// Get the direction of the camera
	Vec3D GetDirection(void);
	void SetPosition( GLfloat x, GLfloat y, GLfloat z );
	void SetDirection( GLfloat x, GLfloat y, GLfloat z );

	void Pitch(GLfloat theta);
	void Yaw(GLfloat theta);
	void Roll(GLfloat theta);
	void Walk(GLfloat delta);//, bool Wall[4]);
	void Strafe(GLfloat delta);//, bool Wall[4]);
	void Fly(GLfloat delta);
	// Toggle HUD mode
	void SetHUD(bool m_bHUDmode);
};
