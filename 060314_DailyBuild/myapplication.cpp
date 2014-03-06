#include "myapplication.h"
#include <mmsystem.h>
#include "Camera\Camera.h"

#include "Managers\ObjectManager.h"
#include "Managers\GameManager.h"
#include "Managers\CollisionManager.h"

#include "Systems\EnemySpawner.h"
#include "SaveGame\SaveManager.h"
#include "Entities\PowerUps\PowerUpManager.h"

#include "Entities\Ship\Ship.h"


myApplication * myApplication::s_pInstance = NULL;

// you can use constructor to initialise variables
myApplication::myApplication()
	:theCamera(NULL)
{
}

myApplication::~myApplication()
{
	if ( theCamera != NULL )
	{
		delete theCamera;
	}

	enableShoot = true;
}

myApplication* myApplication::getInstance()
{
	if(s_pInstance == NULL)
	{
		s_pInstance = new myApplication();
	}

	return s_pInstance;
}

void myApplication::changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = (float) (1.0f* w / h);

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
}

void myApplication::inputKey(int key, int x, int y) {

	//switch (key) {
	//	case GLUT_KEY_LEFT : 
	//		moveMeSideway(true, 1.0f);break;
	//	case GLUT_KEY_RIGHT : 
	//		moveMeSideway(false, 1.0f);break;
	//	case GLUT_KEY_UP : 
	//		moveMeForward(true, 1.0f);break;
	//	case GLUT_KEY_DOWN : 
	//		moveMeForward(false, 1.0f);break;
	//}
}

void myApplication::KeyboardDown(unsigned char key, int x, int y){

	myKeys[key]= true;
}

void myApplication::KeyboardUp(unsigned char key, int x, int y){

	myKeys[key]= false;
}

void myApplication::MouseMove (int x, int y) {
	mouseInfo.lastX = x - Global::HEIGHT_RESOLUTION/2;
	mouseInfo.lastY = Global::WIDTH_RESOLUTION/2 - y;
	
	////Checking mouse boundary. 
	//// 800 is the window width. 
	//// You may need to change this to suit your program.
	//if (mouseInfo.lastX > 800-20 || mouseInfo.lastX < 20)
	//{
	//	mouseInfo.lastX = (800 >> 1);
	//	glutWarpPointer(mouseInfo.lastX, mouseInfo.lastY);
	//}
	//// 600 is the window height. 
	//// You may need to change this to suit your program.
	//if (mouseInfo.lastY > 600-20 || mouseInfo.lastY < 20)
	//{
	//	mouseInfo.lastY = (600 >> 1);
	//	glutWarpPointer(mouseInfo.lastX, mouseInfo.lastY);
	//}
}

void myApplication::MouseClick(int button, int state, int x, int y) 
{
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{	
		mouseInfo.mLButtonDown = true;	
	}
	else
	{
		mouseInfo.mLButtonDown = false;
	}
}


//-------------------------------------------------------------------------
// Calculates the frames per second
//-------------------------------------------------------------------------
void myApplication::calculateFPS()
{
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if(timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
	}

}

//-------------------------------------------------------------------------
//  Draw FPS
//-------------------------------------------------------------------------
void myApplication::drawFPS()
{
	glPushMatrix();
		//  Load the identity matrix so that FPS string being drawn
		//  won't get animates
		glLoadIdentity ();
		glPushAttrib(GL_DEPTH_TEST);
		glDisable(GL_DEPTH_TEST);

			//  Print the FPS to the window
			if (fps > 28.30f)
				glColor3f( 0.0f, 1.0f, 1.0f);
			else if (fps > 28.0f)
				glColor3f( 0.0f, 1.0f, 0.0f);
			else 
				glColor3f( 1.0f, 0.0f, 0.0f);
			printw ( 25.0, 25.0, 0, "FPS: %4.2f", fps );

		glPopAttrib();
		glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

//-------------------------------------------------------------------------
//  Draws a string at the specified coordinates.
//-------------------------------------------------------------------------
void myApplication::printw (float x, float y, float z, char* format, ...)
{
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1; 

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);

	//  Specify the raster position for pixel operations.
	glRasterPos3f (x, y, z);


	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);

	//  Free the allocated memory for the string
	free(text);
}


bool myApplication::Init(void)
{
	// Set camera position
	theCamera = new ippCamera( ippCamera::LAND_CAM );
	theCamera->SetPosition( 0.0, 2.0, -5.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );

	glEnable(GL_TEXTURE_2D);			// Enable Texture Mapping
	glDisable(GL_TEXTURE_2D);

	//  The number of frames
	frameCount = 0;
	//  Number of frames per second
	fps = 0;

	currentTime = 0, previousTime = 0;

	font_style = GLUT_BITMAP_HELVETICA_18;

	// realtime loop control
	Global::curFrameTime=timeGetTime();
	Global::prevFrameTime = Global::curFrameTime;

	frequency = 35.0f;

	for(int i=0; i<255; i++)
	{
		myKeys[i] = false;
	}
	mouseInfo.mLButtonDown = false;

	/*
	===========================================
	Any user created initialization codes 
	should be placed here onwards.
	===========================================
	*/
	
	/*
	===========================================
	Init the save file
	===========================================
	*/

	if ( ! ( ippSaveManager::GetInstance()->Init( "GameUpgrades.txt" ) ) )
	{
		// Adding all the catagories
		ippSaveManager::GetInstance ()->AddCategory ( "BULLETSPEED" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "1", "BULLETSPEED" );

		ippSaveManager::GetInstance ()->AddCategory ( "BULLETLEVEL" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "2", "BULLETLEVEL" );

		ippSaveManager::GetInstance ()->AddCategory ( "MISSILESPEED" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "1", "MISSILESPEED" );

		ippSaveManager::GetInstance ()->AddCategory ( "MISSILETURNSPEED" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "5", "MISSILETURNSPEED" );

		ippSaveManager::GetInstance ()->AddCategory ( "SHIPSPEED" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "1", "SHIPSPEED" );

		ippSaveManager::GetInstance ()->AddCategory ( "SHIPEVASION" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "1", "SHIPEVASION" );

		ippSaveManager::GetInstance ()->AddCategory ( "DRONERATE" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "1", "DRONERATE" );

		// Bank for money!!!
		ippSaveManager::GetInstance ()->AddCategory ( "BANK" );
		ippSaveManager::GetInstance ()->AddInformationInto ( "0", "BANK" );
	}
//////////////////////////////////////////////////////////////////////////////

	// Starting lua
	lua_State *L = lua_open();

	// Load the libs
	luaL_openlibs(L);
	// Loading the lua file
	if(luaL_loadfile(L, "config.lua") || lua_pcall(L, 0, 0, 0))
	{
		printf("Error: &s", lua_tostring(L, -1));
	}
	
	lua_getglobal(L, "SHIPSIZEX");
	float SHIPSIZEX = (float)lua_tonumber(L, -1);

	lua_getglobal(L, "SHIPSIZEY");
	float SHIPSIZEY = (float)lua_tonumber(L, -1);
	

	// Getting the levels from the save file
	int shipSpeed = ippSaveManager::GetInstance ()->GetInt ( "SHIPSPEED" );
	int shipEvasion = ippSaveManager::GetInstance ()->GetInt ( "SHIPEVASION " );


	playerShip = new ippShip (Global::WIDTH_RESOLUTION/2, Global::HEIGHT_RESOLUTION - 25, 0.0f, SHIPSIZEX, SHIPSIZEY );
	playerShip->Init( shipSpeed, shipEvasion );

	ippGameManager::GetInstance()->Init();

	lua_close(L);
	return true;
}
void myApplication::Update(void) 
{
	if( myKeys[27] == true )
		glutLeaveMainLoop();
	
	if ( GetAsyncKeyState(VK_LEFT) )
	{
		playerShip->Movement(ippShip::LEFT);
	}
	
	if ( GetAsyncKeyState(VK_RIGHT) )
	{
		playerShip->Movement(ippShip::RIGHT);
	} 

	if ( GetAsyncKeyState ( VK_SPACE ) )
	{
		if ( enableShoot == true )
		{
			playerShip->FireBullet();
			enableShoot = false;
		}
	}
	else
	{
		enableShoot = true;
	}

	if ( GetAsyncKeyState ( VK_RETURN ) )
	{
		if ( ippObjectManager::GetInstance ()->GetRandomObjByTag ( "Enemy" ) != NULL )
		{
			playerShip->FireMissile ( ippObjectManager::GetInstance ()->GetRandomObjByTag ( "Enemy" ) );
		}
	}

	ippObjectManager::GetInstance()->Update();
}
void myApplication::Render(void) {
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	theCamera->Update();

	ippGameManager::GetInstance()->Update();
	ippCollisionManager::GetInstance()->Update();
	if ((timeGetTime()- Global::prevFrameTime)>1000/frequency)
	{
		// Calculate the framerate
		calculateFPS();
		Global::prevFrameTime = Global::curFrameTime;
		Global::curFrameTime = timeGetTime();
		
	
		Global::timedelta = 1000 / this->fps / (Global::curFrameTime - Global::prevFrameTime);

		//Temporary fix. 
		//Make the game wait 5 seconds before starting as the starting fps affects movement
		if ( fps < 5 )
			Global::timedelta = 1;

		Global::prevFrameTime = Global::curFrameTime;
		Update();
	}
	// Enable 2D text display and HUD

	theCamera->SetHUD( true );
	
	ippObjectManager::GetInstance()->Render();
	ippGameManager::GetInstance()->Render();

	drawFPS();
	theCamera->SetHUD( false );	

	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();
	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}
void myApplication::TestRender ()
{
	Vec3D dimensions(200.0f, 592.0f, 0);
		
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	
	
	glPushMatrix();
		glTranslatef(596, 4, 0);
		glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
		glBegin(GL_QUADS);
			glTexCoord2f( 0, 1 ); glVertex2f( 0, 0);
			glTexCoord2f( 0, 0 ); glVertex2f( 0, dimensions.y);
			glTexCoord2f( 1, 0 ); glVertex2f( dimensions.x, dimensions.y );
			glTexCoord2f( 1, 1 ); glVertex2f( dimensions.x, 0);
		glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

}