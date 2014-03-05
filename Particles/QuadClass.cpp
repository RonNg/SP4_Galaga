#include "QuadClass.h"

ippQuadClass::ippQuadClass(void)
{
	tex = qX = qY = length = width = rotVal = 0.0f;
	texNext = r = g = b = alpha = 1.0f;
}

ippQuadClass::~ippQuadClass(void)
{
}

void ippQuadClass::MaxAlpha()
{
	this->alpha = 1.0f;
}

void ippQuadClass::ReduceAlpha( float value )
{
	this->alpha -= value;
}

void ippQuadClass::SetRGBA ( float r, float g, float b, float alpha )
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->alpha = alpha;
}

void ippQuadClass::SetXY ( float qX, float qY )
{
	this->qX = qX;
	this->qY = qY;
}

void ippQuadClass::SetLW ( float length, float width )
{
	this->length = length;
	this->width = width;
}

void ippQuadClass::SetTex ( float tex, float texNext )
{
	this->tex = tex;
	this->texNext = texNext;
}

void ippQuadClass::SetRotation ( float rotVal )
{
	this->rotVal = rotVal;
}

float ippQuadClass::GetX ()
{
	return qX;
}

float ippQuadClass::GetY ()
{
	return qY;
}

float ippQuadClass::GetLength ()
{
	return length;
}

float ippQuadClass::GetWidth ()
{
	return width;
}

void ippQuadClass::DrawQuads ()
{
	glPushMatrix();

	//glRotatef ( rotVal, 0.0f, 0.0f, 1.0f );

	glColor4f ( r, g, b, alpha );
	glEnable ( GL_BLEND );//Blending for alpha effects
	glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture.texID);

	glBegin ( GL_QUADS );

	//Draws the size of the quads according to the length and width
		/*glTexCoord2f(tex, 0.0f);*/		glVertex2f ( qX - (length/2), qY - (width/2) );
		/*glTexCoord2f(texNext, 0.0f);*/	glVertex2f ( qX + (length/2), qY - (width/2) );
		/*glTexCoord2f(texNext, 1.0f);*/	glVertex2f ( qX + (length/2), qY + (width/2) );
		/*glTexCoord2f(tex, 1.0f);*/		glVertex2f ( qX - (length/2), qY + (width/2) );

	glEnd();

	//glDisable(GL_TEXTURE_2D);
	glDisable ( GL_BLEND );
	glPopMatrix ();
}