#include <stdio.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "idCamera.h"


#define HEIGHT_RESOLUTION 600
#define WIDTH_RESOLUTION 800

//Mouse Info
typedef struct {
	bool mLButtonUp;
	bool mLButtonDown;
	bool mRButtonUp;
	bool middleButtonUp;
	int  lastX, lastY;
} theMouseInfo;


class myApplication 
{
public:
	// this is a constructor, it is implemented in myapplication.cpp
	myApplication();
	// this is a destructor, it is implemented in myapplication.cpp
	~myApplication();

	static myApplication* getInstance();
	static myApplication *s_pInstance;

	bool Init();

	void changeSize(int w, int h);

	void inputKey(int key, int x, int y);
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMove (int x, int y);
	void MouseClick(int button, int state, int x, int y);

	void TestRender();

	bool myKeys[255];
	theMouseInfo mouseInfo;

	// The camera
	idCamera* theCamera;


	void					Update(void);
	void					Render(void);

	//  The number of frames
	int frameCount;
	//  Number of frames per second
	float fps;
	//  currentTime - previousTime is the time elapsed
	//  between every call of the Idle function
	int currentTime, previousTime;
	//  Pointer to a font style..
	//  Fonts supported by GLUT are: GLUT_BITMAP_8_BY_13, 
	//  GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10, 
	//  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
	//  GLUT_BITMAP_HELVETICA_12, and GLUT_BITMAP_HELVETICA_18.
	//GLvoid *font_style;
	void *font_style;
	// Calculate the FPS
	void calculateFPS();
	// Display FPS
	void drawFPS();
	//  Draws a string at the specified coordinates.
	void printw (float x, float y, float z, char* format, ...);

	// realtime loop control
	long timelastcall;
	// realtime loop control - frequency
	float frequency;

};