#pragma once
#include <vector>

class ippPowerUp;

class ippPowerUpManager
{
public:
	ippPowerUpManager(void);
	~ippPowerUpManager(void);

	ippPowerUp* powerUp;

	void Init ();
	void Update ();

private:
	/*int powerUpIndex;
	int maxNumOfPower;*/	// Max number of powerup in the circular buffer

	float delay;
	float curTime;
};