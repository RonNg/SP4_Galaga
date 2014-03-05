#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <Xinput.h>
#include <string>
#pragma comment ( lib, "XInput.lib" )

class ippController
{
public:
	ippController(void);
	~ippController(void);

	ippController ( int playerNumber );
    XINPUT_STATE	GetState();
    bool			IsConnected();
    void			Vibrate ( int leftVal = 0, int rightVal = 0 );

private:
	XINPUT_STATE	controllerState;
	int				controllerNum;
};

