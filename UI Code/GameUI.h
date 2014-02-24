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
	Button (char* G,int nx, int ny);
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
//		Menus
//====================
class Menu
{
private:
	TextureImage	Texture;
public:
	char* name;
	std::vector<Button> MenuButtons;
	Menu (char* Name,char* filename);
	~Menu(void);
	void Render (void);
};

//====================
//		Game UI
//====================

class GameUI									// Class to handle General Menu
{
private:
	Cursor cursor;
	int Find (char* name);						// finds cursor position
public:
	void Move (char* name);						//Goes to the menu with that name.

	unsigned short current;						//current page you're on (number)
	char* page (void);							//name of page you're on.

	std::vector<Menu> List;
	bool SplashScreen;							// If TRUE = splash screen on
	bool EnterKey;								// For Handling of Enter key being pressed or not
	
	GameUI(void);
	~GameUI(void);


	char* Identity (void); //Name of button cursor is on.
	void Render (void);
	void Update(bool up);

	void AddMenu (char* name,char* filename);
	void AddButton (char* u,int x, int y);				// Handles addition of buttons

	void RenderSplashScreen();							// Renders the SplashScreens
	void RenderGameScreen();							// Renders GameScreen
};

