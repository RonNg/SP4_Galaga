#include <stdio.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include "ippCamera.h"
#include <Windows.h>
#include "ippShip.h"

#include "ippGlobals.h"
using namespace Global;


//Mouse Info
typedef struct
{
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

	static myApplication*	getInstance();
	static myApplication*	s_pInstance;

	void					changeSize(int w, int h);

	void					inputKey(int key, int x, int y);
	void					KeyboardDown(unsigned char key, int x, int y);
	void					KeyboardUp(unsigned char key, int x, int y);
	void					MouseMove (int x, int y);
	void					MouseClick(int button, int state, int x, int y);
	void					Keyboard_EventHandler();


	bool					myKeys[255];

	/*
	====================
	Init

	Initializes everything including variables and objects.
	Do all initializations and variable definitions here instead of the
	constructor.
	====================
	*/
	bool					Init();

	/*
	====================
	Update

	Updates data. This function is called before Render.
	Place all your update code here.
	====================
	*/
	void					Update(void);

	/*
	====================
	Render

	Renders scene. 
	Place all your rendering code here.
	====================
	*/
	void					Render(void);

	// The camera
	ippCamera*				theCamera;
	// The mouse struct
	theMouseInfo			mouseInfo;
	//  The number of frames
	int						frameCount;
	//  Number of frames per second
	float					fps;
	//  currentTime - previousTime is the time elapsed
	//  between every call of the Idle function
	int						currentTime, previousTime;
	void*					font_style;
	// Calculate the FPS
	void					calculateFPS();
	// Display FPS
	void					drawFPS();
	//  Draws a string at the specified coordinates.
	void					printw (float x, float y, float z, char* format, ...);
	// realtime loop control - frequency
	float					frequency;

	/*
	===========================================
	Any user created codes should be placed here onwards.
	Please place function declarations first before variables
	===========================================
	*/
	void					TestRender();


	ippShip*				playerShip;

	

};