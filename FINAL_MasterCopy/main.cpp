#include "main.h"
#include "myapplication.h"
#include <time.h>


#include "irrKlang.h"
using namespace irrklang;

/*
===========================================
Holds all global variables and functions
===========================================
*/



namespace Global
{
	float timedelta = 0;
	float prevFrameTime = 0; // time of previous frame
	float curFrameTime = 0; // time of current frame

	float HEIGHT_RESOLUTION = 600.0f;
	float WIDTH_RESOLUTION = 800.0f;

	ISoundEngine* theSoundEngine = createIrrKlangDevice();

	int RNG ( int low, int high)  
	{
		srand(time(NULL)); 
		return rand() % (high - low + 1) + low;
	}

	bool					JoystickA = false;
	bool					JoystickUp= false;
	bool					JoystickDown = false;
	bool					JoystickLeft = false;
	bool					JoystickRight = false;
	bool					JoyKeyPress = false;
	bool					start = false;
	bool					back = false;
	bool					JoystickLeftTrigger = false;
	bool					JoystickRightTrigger = false;
bool						pauseGame = false;

	
}


void changeSize(int w, int h) {
	myApplication::getInstance()->changeSize(w,h);
}

void renderScene(void) {
	myApplication::getInstance()->Render();
}

void inputKey(int key, int x, int y) {
	myApplication::getInstance()->inputKey(key,x,y);
}

void KeyboardDown(unsigned char key, int x, int y){
	myApplication::getInstance()->KeyboardDown(key,x,y);
}

void KeyboardUp(unsigned char key, int x, int y){
	myApplication::getInstance()->KeyboardUp(key,x,y);
}

void MouseMove(int x, int y){
	myApplication::getInstance()->MouseMove(x,y);
}

void MouseClick(int button, int state, int x, int y){
	myApplication::getInstance()->MouseClick(button, state, x, y);
}

void Joystick(unsigned int buttonMask, int x, int y, int z)
{
	myApplication::getInstance()->Joystick(buttonMask,x,y,z);
}

int main(int argc, char **argv )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 0);
	glutInitWindowSize( WIDTH_RESOLUTION, HEIGHT_RESOLUTION);
	glutCreateWindow("DM2231 Lab");

	glutReshapeFunc(changeSize);


	glutFullScreen();

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

//	glutSpecialFunc(inputKey);
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutJoystickFunc(Joystick, 100);

	glutPassiveMotionFunc(MouseMove);
	glutMotionFunc(MouseMove);

	glutMouseFunc(MouseClick);// for mouse click

	if (myApplication::getInstance()->Init() == true)
		glutMainLoop();
	else
	{
		printf("Error Initialising Program\n");
		return 1;
	}

	return 0;

}

