#pragma once
#include "Vec3D.h"
#include <GL/freeglut.h>
#include <vector>
#include "BitFont.h"

class Button		//Class to handle button rendering
{
private:
	
	
public:
	Button(int X,int Y);
	~Button(void);

	void Render(void);	// Button Rendering
	bool Hover (int mx, int my);
	int x,y;		// x and y = coordinate of button
	int w,h;		// for future uses 

};

class Cursor		// Class to handle Button Selection
{
	private:
	

	public:
	Cursor(Button* temp = NULL);
	~Cursor(void);

	Button* button;
	void SetCursor(Button* temp) { button = temp; }// Sets cursor to button's position
	void Render(void);	// Renders the Cursor


};

class GameUI		// Class to handle General Menu
{

private:
	std::vector<Button> MenuButtons;
	Cursor cursor;
	

public:
	void Render (void);
	GameUI(void);
	~GameUI(void);

	void Update(bool up);
	void AddButton(int x, int y);
};

