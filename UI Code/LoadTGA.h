#pragma once
#include <stdio.h>
#include "gl/freeglut.h"

typedef struct
{
	GLubyte	*imageData;			// image data
	GLuint	bpp;				// image color depth ( bits per pixel )
	GLuint	width;				// image width
	GLuint	height;				// image height
	GLuint	texID;					// texture id
} TextureImage;


 
bool LoadTGA(TextureImage *texture, char *filename);
