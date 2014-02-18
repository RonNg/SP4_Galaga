#include <windows.h>		
#include <math.h>			
#include <stdio.h>			
#include <stdarg.h>			
#include <gl\gl.h>			
#include <gl\glu.h>			
#include "BitFont.h"

GLuint	base;

GLvoid BuildFont(GLvoid)								// Build Our Bitmap Font
{
	HDC hDC = GetDC(0);
	HFONT	font;										
	HFONT	oldfont;									

	base = glGenLists(96);								

	font = CreateFont(	-24,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects Font
	wglUseFontBitmaps(hDC, 32, 96, base);				
	SelectObject(hDC, oldfont);							
	DeleteObject(font);									
}

GLvoid KillFont(GLvoid)									
{
	glDeleteLists(base, 96);							
}

GLvoid glPrint(const char *fmt, ...)					
{
	if (fmt == NULL)									
		return;	

	char		text[256];								
	va_list		ap;															

	va_start(ap, fmt);									
	    vsprintf(text, fmt, ap);						
	va_end(ap);											

	glPushAttrib(GL_LIST_BIT);							
		glListBase(base - 32);								
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	
	glPopAttrib();										
}

