#include "myapplication.h"
#include <mmsystem.h>

myApplication * myApplication::s_pInstance = NULL;




// you can use constructor to initialise variables
myApplication::myApplication()
	:theCamera(NULL)
{
	BuildFont();
}

myApplication::~myApplication()
{
	if ( theCamera != NULL )
	{
		delete theCamera;
	}
	KillFont();
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
	if(!myKeys[27])
	theGameUI->keypress=true;
}

void myApplication::KeyboardUp(unsigned char key, int x, int y){

	myKeys[key]= false;
	theGameUI->keypress=false;
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
	glColor3f( 1, 1, 1);
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
	theGameUI = new GameUI();
	// Set camera position
	theCamera = new ippCamera( ippCamera::LAND_CAM );
	theCamera->SetPosition( 0.0, 2.0, -5.0 );
	theCamera->SetDirection( 0.0, 0.0, 1.0 );


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

	frequency = 30.0f;

	for(int i=0; i<255; i++)
	{
		myKeys[i] = false;
	}
	mouseInfo.mLButtonDown = false;

	theGameUI->AddButton("Start",400,350);
	theGameUI->AddButton("Options",400,250);
	theGameUI->AddButton("Quit",400,150);


		/*
	===========================================
	Any user created initialization codes 
	should be placed here onwards.
	===========================================
	*/

	return true;
}
void myApplication::Update(void) 
{
	if( myKeys[27] == true )
		glutLeaveMainLoop();
	if(	myKeys['w'] == true)
	{
		theGameUI->Update(true);

	}
	else if ( myKeys['s'] == true)
	{
		theGameUI->Update(false);
	}

	//if(myKeys[13] == true)					// edit this to check enter key against button
	//{
	//	
	//}


}
void myApplication::Render(void) {
	// Clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	theCamera->Update();

	if ((timeGetTime()- Global::prevFrameTime)>1000/frequency)
	{
		// Calculate the framerate
		calculateFPS();
		Global::prevFrameTime = Global::curFrameTime;
		Global::curFrameTime = timeGetTime();
		Global::timedelta = (Global::curFrameTime - Global::prevFrameTime) / frequency; // Time in seconds
		Global::prevFrameTime= Global::curFrameTime;
		
		Update();	
	}

	// Enable 2D text display and HUD
	theCamera->SetHUD( true );
	TestRender();

	if(theGameUI->SplashScreen)
	{
		theGameUI->RenderSplashScreen();	
	}

		theGameUI->Render();

	
	//drawFPS();


	theCamera->SetHUD( false );

	

	// Flush off any entity which is not drawn yet, so that we maintain the frame rate.
	glFlush();

	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
}



void myApplication::TestRender ()
{

	Vec3D dimensions(20.0f, 20.0f, 0);
		
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
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