#pragma once

#include "irrKlang.h"

using namespace irrklang;

class CSound
{
	static CSound* instance_;
public:

	static CSound* instance(void);
	enum SNUM
	{
		//Menu sounds
		CHOOSE,
		SELECT,
		//Gameplay sounds
		HIT,
		JUMP,
		SHOOT
	};

	//Sounds
	ISoundEngine* theSoundEngine;

	//Background music
	ISound* BGM;

	CSound();
	~CSound();

	void initSound();

	void setMuteBGM(bool muteBGM);
	void setMuteSound(bool muteSound);
	void setMuteHit(bool muteHit);
	void setMuteJump(bool muteJump);

	bool getMuteBGM();
	bool getMuteSound();
	bool getMuteHit();
	bool getMuteJump();
	

	void playSound(SNUM state);
	void playBGM();

private:
	bool muteBGM;
	bool muteSound;
	bool muteHit;
	bool muteJump;
};
