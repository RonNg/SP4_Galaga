#pragma once

#include <time.h>

#include "irrKlang.h"
using namespace irrklang;

namespace Global
{
	extern float prevFrameTime; // time of previous frame
	extern float curFrameTime; // time of current frame
	extern float timedelta;

	extern float HEIGHT_RESOLUTION;
	extern float WIDTH_RESOLUTION;

	extern ISoundEngine* theSoundEngine;
	
	extern int RNG ( int low, int high);
	
	extern bool					JoystickA;
	extern bool					JoystickUp;
	extern bool					JoystickDown;
	extern bool					JoystickLeft;
	extern bool					JoystickRight;
	extern bool					JoyKeyPress;
	extern bool					start;
	extern bool					back;
	extern bool					JoystickLeftTrigger;
	extern bool					JoystickRightTrigger;
	extern bool					pauseGame;
};
