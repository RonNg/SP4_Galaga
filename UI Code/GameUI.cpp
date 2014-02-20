#include "GameUI.h"

using std::vector;


//=================
//		Button
//=================

Button::Button (char* nu,int nx, int ny)
{
	x = nx;
	y = ny;
	u = nu;
}
Button::~Button(void)
{

}

void Button::Render(void)
{

	Vec3D dimensions(75.0f, 35.0f, 0);

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

//====================
//		Cursor
//====================

Cursor::Cursor(Button* temp)
{
	button = temp;
}

Cursor::~Cursor()
{

}

void Cursor::Render(void)
{
	Vec3D dimensions(15.0f, 35.0f, 0);

	glPushMatrix();
	glTranslatef (button->x-100  , button->y , 0);
	glColor3f(1,1,1);
		glBegin(GL_TRIANGLES);
				glVertex2f( dimensions.x, dimensions.y-30);
				glVertex2f( -dimensions.x, -dimensions.y);
				glVertex2f( -dimensions.x,dimensions.y);
			glEnd();               // Done Drawing The triangle
	glPopMatrix();

}

//====================
//		Game UI
//====================


GameUI::GameUI(void)
{


	keypress=false;
	SplashScreen = true;
			glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
	bool isloaded = LoadTGA(&SplashScreenTexture[0],"SplashScreen.tga");			// Load The grass Texture
	

}

GameUI::~GameUI(void)
{

}

void GameUI::Render()
{

	if(SplashScreen)
	{
		if (keypress)
		{
		SplashScreen = false;
		}
	}
	if(!SplashScreen)
	{
	vector<Button>::iterator i = MenuButtons.begin();	// Indicates position of button 
	for (; i != MenuButtons.end(); i++)
	{
		i->Render();
	}
	cursor.Render();
	}

}

void GameUI::Update(bool up)
{
	if(!SplashScreen)
	{
		bool add = false;

		if (!up)
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
			vector<Button>::iterator i = MenuButtons.begin();	// Indicates position of button 
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
}

void GameUI::AddButton (char* u,int x, int y)
{
	if (MenuButtons.size() >= 3)						// Limits Buttons created to 3
	{
		return;
	}
	else if (MenuButtons.size() == 0)
	{
		MenuButtons.push_back(Button(u,x,y));
		cursor.button = &MenuButtons.back();
		return;
	}
	else if (y < MenuButtons.back().y)
	{
		MenuButtons.push_back(Button(u,x,y));
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
	MenuButtons.insert(i,Button(x,y));               // error here
	cursor.button = &MenuButtons.back();
}

void GameUI::RenderSplashScreen()
{	
	
	glPushMatrix();
	Vec3D splashsize (800.0f,600.0f,0);
	glBindTexture(GL_TEXTURE_2D, SplashScreenTexture[0].texID);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(0,splashsize.y);
	glTexCoord2f(1, 0); glVertex2f(splashsize.x, splashsize.y);
	glTexCoord2f(1, 1); glVertex2f(splashsize.x, 0);
	glTexCoord2f(0, 1); glVertex2f( 0,  0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	if(SplashScreen)
	{
	static float colortemp = 1.0f;							// temp for color changing



	glColor3f(colortemp,colortemp,colortemp);
	glRasterPos2f(225,525);
	glPrint("[PRESS ANY KEY TO CONTINUE]");
	colortemp-=0.03f;

	if(colortemp <=0.0f)
	colortemp = 1.0f;
	}

}

char* GameUI::Identity (void)
{
	return cursor.button->u;
}