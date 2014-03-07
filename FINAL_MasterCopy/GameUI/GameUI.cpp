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
	glColor3f(0,0,0);
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
	
	alphaValue = 0.0f;
	sizeOfImage = Vec3D( 800.0f, 600.0f, 0.0f );
	positionOfImage = Vec3D( 400.0f, 300.0f, 0.0f );

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

	glColor4f ( 1.0f, 1.0f, 1.0f, alphaValue );
	glEnable ( GL_BLEND );
	glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glBindTexture(GL_TEXTURE_2D, Texture.texID);
	glEnable(GL_TEXTURE_2D);
	glTranslatef( positionOfImage.x, positionOfImage.y, positionOfImage.z );
		glBegin(GL_QUADS);
			glTexCoord2f(0, 0); glVertex2f(-sizeOfImage.x/2, sizeOfImage.y/2);
			glTexCoord2f(1, 0); glVertex2f(sizeOfImage.x/2, sizeOfImage.y/2);
			glTexCoord2f(1, 1); glVertex2f(sizeOfImage.x/2, -sizeOfImage.y/2);
			glTexCoord2f(0, 1); glVertex2f(-sizeOfImage.x/2,-sizeOfImage.y/2);
		glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable ( GL_BLEND );
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
	
	PreviousPage = 0;
	fadeIn = true;
	fadeOut = false;
	transition = false;
	goToPage = NULL;
}

GameUI::~GameUI(void)
{
	List.clear();
}

void GameUI::Render()									// Renders main menu items
{
	printf( "%3.3f\n", List[current].GetAlpha() );
	if( transition == true )
	{
		if( List[current].GetAlpha() <= 0.0f )
		{
			Move( goToPage );
			fadeIn = true;
			transition = false;
		}
	}
	if( fadeIn == true )
	{
		List[current].FadeInAlpha();
		if( List[current].GetAlpha() >= 1.0f )
		{
			fadeIn = false;
		}
	}
	if( fadeOut == true )
	{
		List[current].FadeOutAlpha();
		if( List[current].GetAlpha() <= 0.0f )
		{
			fadeOut = false;
		}
	}
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

	if (iter->MenuButtons.size() >= 9)						// Limits Buttons created to 3
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

void GameUI::RenderSplashText()
{	
	static float colortemp = 1.0f;				// temp forcolor changing
		glColor3f(colortemp,colortemp,colortemp);
		glRasterPos2f(225,525);
		glPrint("[PRESS ANY KEY TO CONTINUE]");
		colortemp-=0.005f;
		if(colortemp <=0.0f)
		colortemp = 1.0f;
	glColor3f(1,1,1);
}

void GameUI::RenderMainMenuText()
{
		glColor3f(1,1,1);
		glRasterPos2f(360,450);
		glPrint("Start");

		glColor3f(1,1,1);
		glRasterPos2f(360,500);
		glPrint("Shop");

		glColor3f(1,1,1);
		glRasterPos2f(360,550);
		glPrint("Quit");
}

void GameUI::RenderShopText()
{
		glColor3f(0,0,0);
		glRasterPos2f(360,57);
		glPrint("Ship Speed");

		glColor3f(0,0,0);
		glRasterPos2f(360,107);
		glPrint("Ship Evasion");

		glColor3f(0,0,0);
		glRasterPos2f(360,157);
		glPrint("Bullet Speed");

		glColor3f(0,0,0);
		glRasterPos2f(360,207);
		glPrint("Bullet Level");

		glColor3f(0,0,0);
		glRasterPos2f(360,257);
		glPrint("Missile Speed");

		glColor3f(0,0,0);
		glRasterPos2f(360,307);
		glPrint("Missile Turn Speed");

		glColor3f(0,0,0);
		glRasterPos2f(360,357);
		glPrint("Drone Fire Rate");

		glColor3f(0,0,0);
		glRasterPos2f(360,407);
		glPrint("Back");
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
	else if ( name == "Game Over" )
	{
		PreviousPage = current;
		current = Find (name);

		if ( !(List.begin()+current)->MenuButtons.empty() )
			cursor.button = &(List.begin()+current)->MenuButtons.back();
		List[current].SetAlpha(1.0f);
		List[current].SetSize( Vec3D (500, 200, 0 ) );
		List[current].SetPos ( Vec3D (400, 150, 0 ) );

		return;
	}
	else 
	{
		PreviousPage = current;
		current = Find(name);
	}
	if ( !(List.begin()+current)->MenuButtons.empty() )
		cursor.button = &(List.begin()+current)->MenuButtons.back();
	List[current].SetAlpha(1.0f);
}

void GameUI::MoveWithTransition(char* name)
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
