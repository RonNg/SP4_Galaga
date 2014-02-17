#include "ippShip.h"

In Init:

playerShip = new ippShip(0, Global::HEIGHT_RESOLUTION - 25, 0);
playerShip->Init();
playerShip->SetSpeed(10.0f);


In Update:

playerShip->Update();

In Render
playerShip->Render();

In Keyboard_EventHandler:
if ( GetAsyncKeyState ( VK_ESCAPE) )
{
	glutLeaveMainLoop();
}

if ( GetAsyncKeyState ( VK_LEFT ) )
{
	playerShip->Movement ( playerShip->LEFT );
}

if ( GetAsyncKeyState ( VK_RIGHT ) )
{
	playerShip->Movement ( playerShip->RIGHT );
}