#pragma once

#include "Vec3D.h"

class ippDroneClass
{
public:
	ippDroneClass(void);
	~ippDroneClass(void);

	virtual void Update () = 0;
	virtual void Render () = 0;
	virtual void Init () = 0;

protected:
	Vec3D position;
	Vec3D tPosition;
};

