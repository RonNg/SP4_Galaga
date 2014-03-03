#pragma once

#include <vector>

class ippAsteroid;

class ippAsteroidManager
{
public:
	ippAsteroidManager(void);
	~ippAsteroidManager(void);

	std::vector<ippAsteroid*> asteroidList;

	void Init ( void );
	void Update ( void );

private:
	int asteroidIndex;

	float delay;
	float curTime;
};

