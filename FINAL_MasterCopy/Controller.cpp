#include "Controller.h"


ippController::ippController(void)
{
}

ippController::ippController ( int playerNumber )
{
	// Set the player number to the controller
	controllerNum = playerNumber - 1;
}

ippController::~ippController(void)
{
}

bool ippController::IsConnected ()
{
    ZeroMemory ( &controllerState, sizeof ( XINPUT_STATE ) );

    // Get the state
    DWORD Result = XInputGetState ( controllerNum, &controllerState );

    if(Result == ERROR_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ippController::Vibrate ( int leftVal, int rightVal )
{
    // Create a Vibraton State
    XINPUT_VIBRATION Vibration;

    // Zeroise the Vibration
    ZeroMemory ( &Vibration, sizeof ( XINPUT_VIBRATION ) );

    // Set the Vibration Values
    Vibration.wLeftMotorSpeed = leftVal;
    Vibration.wRightMotorSpeed = rightVal;

    // Vibrate the controller
    XInputSetState( controllerNum, &Vibration );
}