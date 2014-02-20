#pragma once
class ippBasicAI
{
private:
	unsigned int prevState;
	unsigned int curState;

public:
	ippBasicAI(void);
	~ippBasicAI(void);

	enum availableStates_t
	{
		FLYING_IN = 37,
		IN_POSITION_OF_GRID,
		FLY_PAST_PLAYER,
		RETURNING_TO_GRID,
	};

	int GetCurrentState();
	int GetPreviousState();
	void SetCurrentState( int new_state_value );
};

