#include "GameUI.h"

using std::vector;


//=================
//		Button
//=================

Button::Button (char* G,int nx, int ny)
{
	x = nx;
	y = ny;
	u = G;
}
Button::~Button(void)
{

}

void Button::Render(void)
{
	Vec3D dimensions(55.0f, 15.0f, 0);

	glPushMatrix();
	glTranslatef (x,y, 0);
	glColor3f(1,0,1);
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
	Vec3D dimensions(15.0f, 15.0f, 0);

	glPushMatrix();
	glTranslatef (button->x-100  , button->y , 0);
	glColor3f(1,1,1);
		glBegin(GL_TRIANGLES);
				glVertex2f( dimensions.x, dimensions.y);
				glVertex2f( -dimensions.x, dimensions.y);
				glVertex2f( -dimensions.x, -dimensions.y);
			glEnd();               // Done Drawing The triangle
	glPopMatrix();


}

Menu::Menu(char *Name,char* filename)
{
	name = Name;

	glEnable(GL_TEXTURE_2D);
		LoadTGA(&Texture,filename);
	glDisable(GL_TEXTURE_2D);
}

Menu::~Menu (void)
{
	MenuButtons.clear();
}

void Menu::Render (void)
{
	glRasterPos2f(0,10);
	glPushMatrix();
	Vec3D splashsize (800.0f,600.0f,0);
	glBindTexture(GL_TEXTURE_2D, Texture.texID);
	glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex2f(0,splashsize.y);
			glTexCoord2f(1, 0); glVertex2f(splashsize.x, splashsize.y);
			glTexCoord2f(1, 1); glVertex2f(splashsize.x, 0);
			glTexCoord2f(0, 1); glVertex2f( 0,  0);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	for (int i = 0; i < MenuButtons.size() ; i++ )
		(MenuButtons.begin()+i)->Render();
}

//====================
//		Game UI
//====================


GameUI::GameUI(void)
{
	current = -1;
	EnterKey = false;
	SplashScreen = true;
	PreviousPage = 0;
}

GameUI::~GameUI(void)
{
	List.clear();
}

void GameUI::Render()									// Renders main menu items
{
	List[current].Render();

	if ( !List[current].MenuButtons.empty() )
		cursor.Render();
}

void GameUI::Update(bool up)
{
	std::vector<Menu>::iterator itr = List.begin() + current;

	if (itr->MenuButtons.empty() )
		return;

	bool add = false;

	if (!up)
	{
		if(cursor.button == &itr->MenuButtons.front())
		{
			cursor.button = &itr->MenuButtons.back();
			return;
		}
		vector<Button>::reverse_iterator i = itr->MenuButtons.rbegin();
		for (; i != itr->MenuButtons.rend(); i++)
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
		if (cursor.button == &itr->MenuButtons.back())
		{
			cursor.button = &itr->MenuButtons.front();
			return;
		}
		vector<Button>::iterator i = itr->MenuButtons.begin();	// Indicates position of button 
		for (; i != itr->MenuButtons.end(); i++)
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

void GameUI::AddMenu (char* name, char* filename)
{
	PreviousPage = current;
	List.push_back(Menu(name,filename) );
	current++;
}

void GameUI::AddButton (char* u,int x, int y)
{
	std::vector<Menu>::iterator iter = (List.begin()+current);

	if (iter->MenuButtons.size() >= 4)						// Limits Buttons created to 3
	{
		return;
	}
	else if (iter->MenuButtons.size() == 0)
	{
		iter->MenuButtons.push_back(Button(u,x,y));
		cursor.button = &iter->MenuButtons.back();
		return;
	}
	else if (y < iter->MenuButtons.back().y)
	{
		iter->MenuButtons.push_back(Button(u,x,y));
		cursor.button = &iter->MenuButtons.back();
		return;
	}

	vector<Button>::iterator i = iter->MenuButtons.begin();	// Indicates position of button 
	for (; i != iter->MenuButtons.end(); i++)
	{
		if( i->y < y)
		{
			break;
		}
	}
	iter->MenuButtons.insert(i,Button(u,x,y));             
	cursor.button = &iter->MenuButtons.back();
}

void GameUI::RenderSplashScreen()
{	
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
	glColor3f(1,1,1);

}

void GameUI::RenderGameScreen()
{
	glPrint("HI-SCORE");			// include highscore
	glPrint("1UP");					// Render lives accordingly
	glPrint("STAGE");				// Update Stage according to level number
	
}

int GameUI::Find (char* name)
{
	std::vector<Menu>::iterator itr;
	for (itr = List.begin() ; itr != List.end() ; itr++ )
	{
		if (itr->name == name)
			return std::distance(List.begin(),itr);
	}
	return -1;						// if it returns negative , means buttons missing/broken
}

void GameUI::Move (char* name)
{
	if (name == "Back")
	{
		current = PreviousPage;
		PreviousPage = current;
	}
	else 
	{
		PreviousPage = current;
		current = Find(name);
	}
	if ( !(List.begin()+current)->MenuButtons.empty() )
		cursor.button = &(List.begin()+current)->MenuButtons.back();
}

char* GameUI::page (void)
{
	return (List.begin()+current)->name;
}

char* GameUI::Identity (void)
{
	return cursor.button->u;
}
