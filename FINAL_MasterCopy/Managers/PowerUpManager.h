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
	float delay;
	float prevTime;
	float curTime;
};