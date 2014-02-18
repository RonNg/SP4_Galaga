#include "main.h"
#include "myapplication.h"

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

	int HEIGHT_RESOLUTION = 600;
	int WIDTH_RESOLUTION = 800;
};

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

int main(int argc, char **argv )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize( WIDTH_RESOLUTION, HEIGHT_RESOLUTION);
	glutCreateWindow("DM2231 Lab");

	glutReshapeFunc(changeSize);

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

//	glutSpecialFunc(inputKey);
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);

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

