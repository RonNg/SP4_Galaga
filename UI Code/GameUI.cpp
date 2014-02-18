#include "GameUI.h"

Vec3D dimensions(75.0f, 35.0f, 0);
using std::vector;

Button::Button(int X, int Y)
{
	x = X;
	y = Y;

}

Button::~Button(void)
{

}

bool Button::Hover(int mx, int my)
{
	return true;
}

void Button::Render(void)
{
	glPushMatrix();
	glTranslatef (x,y, 0);
	glColor3f(1,1,1);
	  glBegin(GL_QUADS);                      // Draw A Quad
	  glVertex2f(-dimensions.x, dimensions.y);              // Top Left
        glVertex2f( dimensions.x, dimensions.y);              // Top Right
        glVertex2f( dimensions.x,-dimensions.y);              // Bottom Right
        glVertex2f(-dimensions.x,-dimensions.y);              // Bottom Left
    glEnd();                            // Done Drawing The Quad
	glPopMatrix();

}

Cursor::Cursor(Button* temp)
{
	button = temp;
}

Cursor::~Cursor()
{

}

void Cursor::Render(void)
{

	glPushMatrix();
	glTranslatef (button->x-100  , button->y , 0);
	glColor3f(1,1,1);
		glBegin(GL_TRIANGLES);
				glVertex2f( dimensions.x/3, dimensions.y/4);
				glVertex2f( -dimensions.x/3, -dimensions.y);
				glVertex2f( -dimensions.x/3,dimensions.y);
			glEnd();               // Done Drawing The triangle
	glPopMatrix();

}

GameUI::GameUI(void)
{

}


GameUI::~GameUI(void)
{

}

void GameUI::Render()
{
	vector<Button>::iterator i = MenuButtons.begin();	// Indicates position of button 
	for (; i != MenuButtons.end(); i++)
	{
		i->Render();
	}
	cursor.Render();
}

void GameUI::Update(bool up)
{
	bool add = false;
	
	if (up)
	{
		if(cursor.button == &MenuButtons.front())
		{
			cursor.button = &MenuButtons.back();
			return;
		}
		vector<Button>::reverse_iterator i = MenuButtons.rbegin();
		for (; i != MenuButtons.rend(); i++)
		{
			if (add)
			{
				cursor.button = &*i;
				return;
			}
			else if (&*i == cursor.button) 
			{
				add = true;
			}
		}
	}
	else
	{
		if (cursor.button == &MenuButtons.back())
		{
			cursor.button = &MenuButtons.front();
			return;
		}
		vector<Button>::iterator i = MenuButtons.begin();// Indicates position of button 
		for (; i != MenuButtons.end(); i++)
		{
			if (add)
			{
				cursor.button = &*i;
				return;
			}
			else if (&*i == cursor.button) 
			{
				add = true;
			}
		}
	}
}

void GameUI::AddButton(int x, int y)
{
	if (MenuButtons.size() >= 3)						// Limits Buttons created to 3
	{
		return;
	}
	else if (MenuButtons.size() == 0)
	{
		MenuButtons.push_back(Button(x, y));
		cursor.button = &MenuButtons.back();
		return;
	}
	else if (y < MenuButtons.back().y)
	{
		MenuButtons.push_back(Button(x, y));
		cursor.button = &MenuButtons.back();
		return;
	}

	vector<Button>::iterator i = MenuButtons.begin();	// Indicates position of button 
	for (; i != MenuButtons.end(); i++)
	{
		if( i->y < y)
		{
			break;
		}
	}
	MenuButtons.insert(i,Button(x,y));
	cursor.button = &MenuButtons.back();
}
