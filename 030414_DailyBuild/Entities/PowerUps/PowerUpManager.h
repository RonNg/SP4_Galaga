#pragma once
#include <vector>

class ippPowerUp;

class ippPowerUpManager
{
public:
	ippPowerUpManager(void);
	~ippPowerUpManager(void);

	std::vector<ippPowerUp*>powerUpList;

	void Init ();
	void Update ();

private:
	int powerUpIndex;

	float delay;
	float curTime;
};