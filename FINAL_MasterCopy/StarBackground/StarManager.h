#pragma once

#include <vector>

class ippStar;

class ippStarManager
{
public:
	ippStarManager(void);
	~ippStarManager(void);

	std::vector<ippStar*> starList;

	void Init ( void );
	void Update ( void );
	void Render ( void );

private:
	int starIndex;

	float delay;

	float prevTime;
	float curTime;

	int maxStar;
};

