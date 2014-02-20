#pragma once
#include "Vec3D.h"
#include <GL/freeglut.h>
#include <vector>
#include "BitFont.h"
#include "LoadTGA.h"

//===================
//		Button
//===================
class Button								//Class to handle button rendering
{
private:
	
public:
	Button (char* nu,int nx, int ny);
	~Button(void);

	char* u;
	int x,y;								// x and y = coordinate of button
	void Render(void);						// Button Rendering
	
};

//====================
//		Cursor
//====================
class Cursor								// Class to handle Button Selection
{
	private:

	public:
	Cursor(Button* temp = NULL);
	~Cursor(void);

	Button* button;
	void SetCursor(Button* temp) { button = temp; }	// Sets cursor to button's position
	void Render(void);								// Renders the Cursor

};

//====================
//		Game UI
//====================

class GameUI									// Class to handle General Menu
{

private:

	std::vector<Button> MenuButtons;
	Cursor cursor;
	TextureImage SplashScreenTexture[1];

public:

	bool keypress;								// Checker for splash screen, tests if any key was pressed
	bool SplashScreen;							// If TRUE = splash screen on
		
	GameUI(void);
	~GameUI(void);

	Button* button;

	void Render (void);
	void Update(bool up);
	void AddButton (char* u,int x, int y);				// Handles addition of buttons
	char* Identity (void);
	void RenderSplashScreen();					// Renders the SplashScreens
	
};

