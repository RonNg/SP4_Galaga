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
	void CreateType ();

private:
	int powerUpIndex;
};