#pragma once

#include "GL\glut.h"

class ippQuadClass
{
public:
	ippQuadClass(void);
	~ippQuadClass(void);

	//Storing texture in the class
	//CTexture texture;

	void	SetRGBA (float r, float g, float b, float alpha);

	void	SetXY (float qX, float qY);

	void	SetLW (float length, float width);	//Set length and width

	void	SetTex (float tex, float texNext);

	void	SetRotation ( float rotVal );

	float	GetX ();

	float	GetY ();

	float	GetLength ();

	float	GetWidth ();

	void	DrawQuads ();

private:
	float r, g, b, alpha, qX, qY, length, width, tex, texNext, rotVal;
};