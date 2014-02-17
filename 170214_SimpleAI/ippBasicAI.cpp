#include "ippBasicAI.h"


ippBasicAI::ippBasicAI(void)
:	prevState(0)
,	curState(0)
{
}


ippBasicAI::~ippBasicAI(void)
{
}

int ippBasicAI::GetCurrentState()
{
	return curState;
}

int ippBasicAI::GetPreviousState()
{
	return prevState;
}

void ippBasicAI::SetCurrentState( int new_state_value )
{
	prevState = curState;
	curState = new_state_value;
}
